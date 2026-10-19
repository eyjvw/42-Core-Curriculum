/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 16:25:57 by hkeromne          #+#    #+#             */
/*   Updated: 2026/02/24 18:11:30 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"
# include "MSG.hpp"
# include "RPL.hpp"
# include "CMD.hpp"
# include "Errors.hpp"

volatile sig_atomic_t	sigShutdown = 0;

Server::~Server(void)
{
	close(this->fd);
    while (!this->clients.empty())
        this->disconnectClient(this->clients.begin()->second->getFd());
}

Server::Server(std::string password, int port): fd(0), port(port), password(password) {};

bool	Server::init(void)
{
	struct pollfd	p;
	int				reuse = 1;

	this->fd = socket(IPV4, SOCK_STREAM, DEFAULT_PROTOCOL);
	this->fds.reserve(1034);
	if (this->fd == -1 || fcntl(this->fd, F_SETFL, O_NONBLOCK)
	|| setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
		return (false);
	this->addr.sin_family		= IPV4;
	this->addr.sin_addr.s_addr	= ANY_ADDRESS;
	this->addr.sin_port			= PORT;
	
	socklen_t socklen = sizeof(this->addr);
	if (bind(this->fd, (sockaddr *) &this->addr, socklen) == -1
	|| listen(this->fd, 10) == -1)
		return (false);
	p.fd = fd;
	p.events = POLLIN;
	p.revents = 0;
	this->fds.push_back(p);
	this->startTime = Ft::getTime();
	return (true);
}

void	Server::launch(void)
{
	int		fds_ready = 0;

	while (!sigShutdown)
	{
		for (int x = 1; x < (int)this->fds.size(); x++)
			this->fds[x].events = (this->clients[this->fds[x].fd]->getSendBuffer().empty())
				? POLLIN
				: POLLIN | POLLOUT;
		fds_ready = poll(this->fds.data(), this->fds.size(), 10);
		for (int x = 0; x < (int)this->fds.size() && fds_ready > 0; x++)
		{
			int		fd = this->fds[x].fd;
			short	revents = this->fds[x].revents;

			if (!revents)
				continue ;
			fds_ready--;
			if (x == 0)
			{
				if (revents & POLLIN)
					this->acceptClient();
				continue ;
			}
			try
			{
				if (revents & (POLLIN | POLLHUP | POLLERR))
					this->acceptMessage(*(this->clients[fd]));
				if (this->clients.count(fd) && revents & POLLOUT)
					this->clients[fd]->sendMsg();
			}
			catch (std::exception &e)
			{
				std::cerr << "[ERROR] " << e.what() << std::endl;
				if (this->clients.count(fd))
					this->disconnectClient(fd);
			}
			if (x >= (int)this->fds.size() || this->fds[x].fd != fd)
				x--;
		}
		this->dropOverflowed();
	}
}

void	Server::dropOverflowed(void)
{
	std::map<int, Client *>::iterator	it = this->clients.begin();
	Client								*client;

	while (it != this->clients.end())
	{
		client = it->second;
		it++;
		if (!client->getSendQExceeded())
			continue ;
		std::cout << "[INFO] " << client->getNick() << " SendQ exceeded" << std::endl;
		client->broadcastMsg(RPL_STR(client->getNick(), client->getUser(), CMD_QUIT)
			+ RPL_QUIT("Max SendQ exceeded") + "\r\n");
		this->disconnectClient(client->getFd());
	}
}

void	Server::acceptMessage(Client &client)
{
	std::string	line;
	std::string	buffer;

	buffer = Ft::getFdContent(client.getFd());
	if (buffer.empty())
	{
		client.broadcastMsg(RPL_STR(client.getNick(), client.getUser(), CMD_QUIT)
			+ RPL_QUIT("Connection lost") + "\r\n");
		return (this->disconnectClient(client.getFd()));
	}
	while (!buffer.empty())
	{
		line = client.getRecvBuffer() + Ft::extractLine(buffer);
		client.clearRecvBuffer();
		if (!Ft::endsWithLF(line))
			return (client.appendRecvBuffer(line.substr(0, MSG_MAX + 1)));
		line = Ft::toCRLF(line);
		if (line.size() > MSG_MAX)
		{
			package.clear();
			package.client = &client;
			package.setError(ERR_INPUTTOOLONG);
			RPL::reply(*this);
			continue ;
		}
		if (MSG::getCmd(line).empty())
			continue ;
		if (!client.getAuth())
		{
			if (!this->authenticate(client, line))
				return ;
			continue ;
		}
		std::cout << "[CMD] " << line;
		MSG::sendData(&client, line);
		CMD::apply(*this);
		RPL::reply(*this);
		if (package.quit)
			return (this->disconnectClient(client.getFd()));
	}
}

void	Server::acceptClient(void)
{
	int				fd;
	struct pollfd	pfd;

	fd = accept(this->fd, (sockaddr *) NULL, NULL);
	if (fd == -1)
		return ;
	if (this->clients.size() >= FD_MAX || fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
		return ((void)close(fd));

	pfd.fd = fd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	this->fds.push_back(pfd);
	this->clients[pfd.fd] = new Client(this->fds.back().fd);
}

bool	Server::passCheck(std::string const &pass) { return (this->password == pass); };

bool	Server::authenticate(Client &client, std::string const &line)
{
	std::cout << "[AUTH][CMD] " << line;
	MSG::sendData(&client, line);

	if (package.cmd == CMD_QUIT)
		return (this->disconnectClient(client.getFd()), false);
	if (!client.getPass().empty() && (package.cmd == "NICK" || package.cmd == "USER"))
		client.setCanPass(false);
	if ((client.getCanPass() && package.cmd != "PASS")
		|| (!client.getCanPass() && (package.cmd != "NICK" && package.cmd != "USER")))
	{
		package.setError(ERR_NOTREGISTERED);
		RPL::reply(*this);
		return (true);
	}
	else if (!client.getCanPass() && !this->passCheck(client.getPass()))
	{
		package.setError(ERR_PASSWDMISMATCH);
		RPL::reply(*this);
		return (this->disconnectClient(client.getFd()), false);
	}

	CMD::apply(*this);
	RPL::reply(*this);
	if (!client.isAuth(this->password))
		return (true);

	RPL::Welcome((*this), &client, client.getNick());
	client.setAuth(true);
	std::cout << "[AUTH][INFO] " << client.getNick() << " Connected" << std::endl;
	return (true);
}

void	Server::disconnectClient(const int &fd)
{
	Client *client = this->clients[fd];
	
	client->disconnection(*this);
	for (std::map<std::string, Channel>::iterator it = this->channels.begin(); it != this->channels.end(); it++)
	{
		it->second.removeInvited(fd);
		it->second.removeOperator(fd);
	}
	close(client->getFd());
	this->clients.erase(fd);
	for (std::vector<struct pollfd>::iterator it = this->fds.begin(); it != this->fds.end(); it++)
	{
		if (it->fd == fd)
		{
			this->fds.erase(it);
			break ;
		}
	}
	delete (client);
}

std::string const	&Server::getStartTime(void) const				{ return (this->startTime); };

void				Server::createChannel(Channel &channel)			{ this->channels[Ft::toLower(channel.getName())] = channel; };
bool				Server::deleteChannel(std::string const &name)	{ return (this->channels.erase(Ft::toLower(name))); };
bool				Server::isChannel(std::string const &name)		{ return (this->channels.find(Ft::toLower(name)) != this->channels.end()); };

bool				Server::isClient(std::string const &nick)		{ return (this->getClient(nick) != NULL); };
Client				*Server::getClient(int const &id)				{ return (this->clients.find(id)->second); };
Client				*Server::getClient(std::string const &nick)
{
	std::string	lower = Ft::toLower(nick);

	for (std::map<int, Client *>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
	{
		if (!it->second->getNick().empty() && Ft::toLower(it->second->getNick()) == lower)
			return (it->second);
	}
	return (NULL);
}

Channel				*Server::getChannel(std::string const &name)
{
	std::map<std::string, Channel>::iterator it = this->channels.find(Ft::toLower(name));

	return ((it == this->channels.end()) ? NULL : &(it->second));
}

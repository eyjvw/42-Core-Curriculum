/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 16:28:10 by hkeromne          #+#    #+#             */
/*   Updated: 2026/02/24 18:08:59 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Client.hpp"
# include "Server.hpp"

Client::Client(void): auth(false), fd(-1), canPass(true), sendQExceeded(false) {};
Client::~Client(void) {};
Client::Client(int fd): auth(false), fd(fd), canPass(true), sendQExceeded(false) {};
Client::Client(Client const &copy) { (*this) = copy; };

Client &Client::operator=(Client const &copy)
{
	this->fd = copy.fd;
	this->nick = copy.nick;
	this->auth = copy.auth;
	this->canPass = copy.canPass;
	this->sendQExceeded = copy.sendQExceeded;
	this->username = copy.username;
	this->realname = copy.realname;
	this->password = copy.password;
	this->sendBuffer = copy.sendBuffer;
	this->recvBuffer = copy.recvBuffer;
	this->channels = copy.channels;

	return (*this);
}

const int			&Client::getFd(void)		const			{ return (this->fd); };
const bool			&Client::getCanPass(void)	const			{ return (this->canPass); };
const bool			&Client::getAuth(void)		const			{ return (this->auth); };
const bool			&Client::getSendQExceeded(void) const		{ return (this->sendQExceeded); };
const std::string	&Client::getNick(void)		const			{ return (this->nick); };
const std::string	&Client::getName(void)		const			{ return (this->realname); };
const std::string	&Client::getUser(void)		const			{ return (this->username); };
const std::string	&Client::getPass(void)		const			{ return (this->password); };
const std::string	&Client::getSendBuffer(void)	const		{ return (this->sendBuffer); };
const std::string	&Client::getRecvBuffer(void)	const		{ return (this->recvBuffer); };
Channel				*Client::getChannel(std::string const &topic) const { return (this->channels.find(Ft::toLower(topic))->second); };
void				Client::setAuth(bool auth)					{ this->auth = auth; };
void				Client::setCanPass(bool canPass)			{ this->canPass = canPass; };
void				Client::setNick(std::string const &nick)	{ this->nick = nick; };
void				Client::setName(std::string const &name)	{ this->realname = name; };
void				Client::setUser(std::string const &user)	{ this->username = user; };
void				Client::setPass(std::string const &pass)	{ this->password = pass; };
void				Client::appendRecvBuffer(std::string const &buff)	{ this->recvBuffer += buff; };
void				Client::clearSendBuffer(void) { this->sendBuffer.clear(); };
void				Client::clearRecvBuffer(void) { this->recvBuffer.clear(); };
void				Client::addChannel(Channel *channel)		{ this->channels[Ft::toLower(channel->getName())] = channel; };
void				Client::delChannel(std::string const &topic){ this->channels.erase(Ft::toLower(topic)); };
bool				Client::isChannel(std::string const &topic) { return (this->channels.find(Ft::toLower(topic)) != this->channels.end()); };
bool				Client::inChannel(void) const				{ return (!this->channels.size()); };
const std::map<std::string, Channel *> &Client::getChannels(void) const { return (this->channels); }

void				Client::appendSendBuffer(std::string const &buff)
{
	if (this->sendQExceeded)
		return ;
	if (this->sendBuffer.size() + buff.size() > MAX_SENDQ)
	{
		this->sendQExceeded = true;
		return ;
	}
	if (buff.size() > MSG_MAX)
		this->sendBuffer += buff.substr(0, MSG_MAX - 2) + "\r\n";
	else
		this->sendBuffer += buff;
}

void				Client::sendMsg(void)
{
	ssize_t	bytes;

	if (this->sendBuffer.empty())
		return ;
	bytes = send(this->getFd(), this->sendBuffer.c_str(), this->sendBuffer.size(), MSG_NOSIGNAL);
	if (bytes > 0)
		this->sendBuffer.erase(0, bytes);
}

bool				Client::isAuth(std::string const &password)
{
	return (!this->nick.empty()
			&& !this->username.empty()
			&& !this->realname.empty()
			&& this->password == password);
}

void	Client::disconnection(Server &server)
{
	this->sendMsg();
	while (!this->channels.empty())
	{
		Channel *channel = this->channels.begin()->second;
		channel->removeOperator(this->fd);
		channel->removeInvited(this->fd);
		channel->removeClient(this->fd);
		this->delChannel(channel->getName());
		if (channel->getClientAmount() == 0)
			server.deleteChannel(channel->getName());
	}
}

void	Client::broadcastMsg(std::string const &msg)
{
	std::set<Client *>	targets;

	for (std::map<std::string, Channel *>::iterator it = this->channels.begin(); it != this->channels.end(); it++)
	{
		std::map<const int, Client *> const &members = it->second->getClients();
		for (std::map<const int, Client *>::const_iterator m = members.begin(); m != members.end(); m++)
			if (m->second != this)
				targets.insert(m->second);
	}
	for (std::set<Client *>::iterator it = targets.begin(); it != targets.end(); it++)
		(*it)->appendSendBuffer(msg);
}

std::ostream &operator<<(std::ostream &stream, std::map<std::string, Channel *> const &channels)
{
	stream << "===== CHANNELS ======" << std::endl;
	for (std::map<std::string, Channel *>::const_iterator it = channels.begin(); it != channels.end(); it++)
		stream << *(it->second);
	return (stream);
}

std::ostream &operator<<(std::ostream &stream, Client const &client)
{
	stream <<	"==== CLIENT ====" << std::endl;
	stream << "Fd : "	<<	client.getFd() << std::endl; 
	stream << "Name : "	<<	client.getName() << std::endl;
stream << "Nick : "	<<	client.getNick() << std::endl;
	stream << "User : "	<<	client.getUser() << std::endl;
	stream << client.getChannels();

	return (stream);
}

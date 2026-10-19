/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 20:43:39 by hkeromne          #+#    #+#             */
/*   Updated: 2026/02/18 02:07:25 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Mode.hpp"
# include "Errors.hpp"

static std::map<char, void (*)(Server &, bool, int &)> initMode()
{
    std::map<char, void (*)(Server &, bool, int &)> m;

	m[MODE_OP] =		&Mode::o;
	m[MODE_INVITE] =	&Mode::i;
	m[MODE_LIMIT] =		&Mode::l;
	m[MODE_KEY] =		&Mode::k;
	m[MODE_TOPIC] =		&Mode::t;

    return m;
}

std::map<char, void (*)(Server &, bool, int &)> Mode::mode = initMode();

static int	spareArgs = 0;

static bool checkModes(std::string const &modes)
{
	int			args	= 0;
	bool		add		= true;

	package.errMode = modes;
	if (modes[0] != '+' && modes[0] != '-')
		return (package.setError(ERR_UNKNOWNMODE), false);
	for (int i = 0;	i < (int)modes.length(); i++)
	{
		char m = modes[i];
		if (m == '+' || m == '-')
			add = (m == '+');
		else if (m == 'o' || ((m == 'k' || m == 'l') && add))
			args++;
	}
	if (((int)package.cmdData.size() - 2) < args)
		return (package.setError(ERR_NEEDMOREPARAMS), false);
	spareArgs = ((int)package.cmdData.size() - 2) - args;
	return (true);
}

bool	Mode::Check(Server &server)
{
	std::string	set	= CMODES;
	std::string nick = package.client->getNick();
	const int	fd = package.client->getFd();

	if (package.cmdData.size() < 1)
		return (package.setError(ERR_NEEDMOREPARAMS), false);
	std::string chanName = package.cmdData[MODE_CHANNEL];
	package.errChanName = chanName;
	package.errNick = nick;
	if (chanName[0] != '#')
		return (package.setError(-1), false);
	if (!server.isChannel(chanName))
		return (package.setError(ERR_NOSUCHCHANNEL), false);

	package.channel = server.getChannel(chanName);
	if (package.cmdData.size() == 1)
		return (false);
	if (!package.channel->isClient(fd))
		return (package.setError(ERR_NOTONCHANNEL), false);
	if (!package.channel->isOperator(package.client->getFd()) && package.cmdData.size() >= 2)
		return (package.setError(ERR_CHANOPRIVSNEEDED), false);
	return (checkModes(package.cmdData[MODE_MODES]));
}

bool	Mode::singleCheck(char m)
{
	std::string	set = CMODES;

	if (set.find(m) != std::string::npos)
		return (true);
	package.errMode = m;
	return (package.setError(ERR_UNKNOWNMODE), false);
}

void	Mode::o(Server &server, bool add, int &argCount)
{
	std::string nick = package.cmdData[argCount++];
	package.errNick = nick;
	package.errChanName = package.channel->getName();

	if (!server.isClient(nick))
		return (package.setError(ERR_NOSUCHNICK));
	Client		*client = server.getClient(nick);

	if (!package.channel->isClient(client->getFd()))
		return (package.setError(ERR_USERNOTINCHANNEL));
	(add) ? package.channel->addOperator(client) : (void)package.channel->removeOperator(client->getFd());
}

void	Mode::l(Server &server, bool add, int &argCount)
{
	(void)				server;
	int					limit;
	std::stringstream	sNum;

	if (!add)
		return (package.channel->setOpLimit(0));
	std::string arg = package.cmdData[argCount++];
	if (!Ft::isInt(arg))
		return (package.setError(ERR_NEEDMOREPARAMS));
	sNum << arg;
	sNum >> limit;

	if (!sNum.eof() || sNum.fail() || limit <= 0)
		return (package.setError(ERR_NEEDMOREPARAMS));

	package.channel->setOpLimit(limit);
}

void	Mode::i(Server &server, bool add, int &argCount)
{
	(void) server;
	(void) argCount;

	(add) ? package.channel->setOpInvite(true) : package.channel->setOpInvite(false);
}

void	Mode::t(Server &server, bool add, int &argCount)
{
	(void) server;
	(void) argCount;

	(add) ? package.channel->setOpTopic(true) : package.channel->setOpTopic(false);
}

void	Mode::k(Server &server, bool add, int &argCount)
{
	(void) server;
	(void) argCount;

	if (!add)
	{
		if (spareArgs > 0)
		{
			spareArgs--;
			argCount++;
		}
		return (package.channel->setOpKey(false, ""));
	}
	package.channel->setOpKey(true, package.cmdData[argCount++]);
}

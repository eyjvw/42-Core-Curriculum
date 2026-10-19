/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 15:00:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/10/19 15:00:00 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Part.hpp"
# include "Errors.hpp"

bool Part::Check(Server &server)
{
	std::string partChan =	package.cmdData[PART_CHANNEL];
	package.errChanName =	partChan;

	if (!server.isChannel(partChan))
		return (package.setError(ERR_NOSUCHCHANNEL), false);

	Channel		*channel =	server.getChannel(partChan);

	if (!channel->isClient(package.client->getFd()))
		return (package.setError(ERR_NOTONCHANNEL), false);
	package.channel = channel;
	return (true);
}

void Part::Leave(void)
{
	int		fd = package.client->getFd();

	package.channel->removeClient(fd);
	package.channel->removeOperator(fd);
	package.channel->removeInvited(fd);
	package.client->delChannel(package.channel->getName());
}

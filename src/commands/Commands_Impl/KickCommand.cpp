/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:10:11 by sayar             #+#    #+#             */
/*   Updated: 2023/02/15 15:10:12 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/commands/CommandHandler.hpp"

KickCommand::KickCommand(Server *server) : Command(server) {

}

KickCommand::~KickCommand(void) {}

void	KickCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.size() < 2) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "KICK"));
		return ;
	}

	std::string name = arguments[0];
	std::string user = arguments[1];
	std::string reason = "No reason specified..";

	if ((arguments.size() >= 3 && arguments[2][0] != ':') || arguments[2].size() > 1) {
		reason = "";
		for (std::vector<std::string>::iterator it = arguments.begin() + 2; it != arguments.end(); it++) {
			reason.append((*it) + " ");
		}
	}

	Channel *channel = client->getChannel();
	if (!channel || channel->getName() != name) {
		client->reply(ERR_NOTONCHANNEL(client->getNickName(), name));
		return ;
	}

	if (channel->getAdmin() != client) {
		client->reply(ERR_CHANOPRIVSNEEDED(client->getNickName(), name));
		return ;
	}

	Client *target = _server->getClient(user);
	if (!target) {
		client->reply(ERR_NOSUCHNICK(client->getNickName(), user));
		return ;
	}

	channel->kickClient(client, target, reason);

}
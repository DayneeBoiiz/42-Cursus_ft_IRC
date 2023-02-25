/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsgCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:09:31 by slammari          #+#    #+#             */
/*   Updated: 2023/02/25 18:43:24 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/commands/CommandHandler.hpp"

PrivMsgCommand::PrivMsgCommand(Server *server) : Command(server) {}

PrivMsgCommand::~PrivMsgCommand(void) {}

void PrivMsgCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.size() < 2 || arguments[0].empty() || arguments[1].empty()) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "PRIVMSG"));
		return;
	}

	std::string target = arguments.at(0);
	std::string message;

	for (std::vector<std::string>::iterator it = arguments.begin() + 1; it != arguments.end(); it++) {
		message.append(*it + " ");
	}

	message = message.at(0) == ':' ? message.substr(1) : message;

	if (target.at(0) == '#') {

		Channel *channel = _server->getChannel(target);
		if (!channel) {
			client->reply(ERR_NOSUCHCHANNEL(client->getNickName(), target));
			return;
		}

		if (channel->isExt()) {
			std::vector<std::string>			nicknames(channel->getNicknames());
			std::vector<std::string>::iterator	i;

			for (i = nicknames.begin(); i != nicknames.end(); i++)
				if (*i == client->getNickName())
					break;
			if (i == nicknames.end())
			{
				client->reply(ERR_CANNOTSENDTOCHAN(client->getNickName(), target));
				return;
			}
		}

		channel->broadcast(RPL_PRIVMSG(client->getPrefix(), target, message), client);
		return;

	}

	Client *dest = _server->getClient(target);
	if (!dest) {
		client->reply(ERR_NOSUCHNICK(client->getNickName(), target));
		return;
	}

	dest->write(RPL_PRIVMSG(client->getPrefix(), target, message));

}
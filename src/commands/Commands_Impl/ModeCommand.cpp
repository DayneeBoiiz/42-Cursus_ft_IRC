/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:21:49 by sayar             #+#    #+#             */
/*   Updated: 2023/02/17 22:21:01 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/commands/CommandHandler.hpp"

ModeCommand::ModeCommand(Server *server) : Command(server) {

}

ModeCommand::~ModeCommand(void) {

}

void	ModeCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.size() < 2) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "MODE"));
		return ;
	}

	std::string target = arguments[0];

	Channel *channel = _server->getChannel(target);
	if (!channel) {
		client->reply(ERR_NOSUCHCHANNEL(client->getNickName(), target));
		return ;
	}

	if (channel->getAdmin() != client) {
		client->reply(ERR_CHANOPRIVSNEEDED(client->getNickName(), target));
		return ;
	}

	int i = 0;
	int p = 2;

	char c;
	while ((c = arguments[1][i])) {

		char prev = i > 0 ? arguments[1][i - 1] : '\0';
		bool active = prev == '+';

		switch (c) {

			case ('n') : {
				channel->setExt(active);
				channel->broadcast(RPL_MODE(client->getPrefix(), channel->getName(), (active ? "+n" : "-n"), ""));
				break ;
			}

			case ('l') : {
				channel->setMaxClient(active ? std::stol(arguments[p]) : 0);
				channel->broadcast(RPL_MODE(client->getPrefix(), channel->getName(), (active ? "+l" : "-l"), (active ? arguments[p] : "")));
				// p += active ? 1 : 0;
				// std::cout << "======>>>> " << arguments[p] << std::endl;
				break ;
			}

			default :
				break ;
		}
		i++;

	}

}

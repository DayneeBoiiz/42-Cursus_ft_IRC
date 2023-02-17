/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:41:59 by sayar             #+#    #+#             */
/*   Updated: 2023/02/17 21:45:16 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/commands/Command.hpp"

PingCommand::PingCommand(Server *server) : Command(server) {

}

PingCommand::~PingCommand(void) {

}

void	PingCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.empty()) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "PING"));
		return ;
	}

	client->write(RPL_PING(client->getPrefix(), arguments.at(0)));

}
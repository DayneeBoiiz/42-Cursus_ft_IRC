/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:46:23 by sayar             #+#    #+#             */
/*   Updated: 2023/02/17 21:47:39 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/commands/Command.hpp"

PongCommand::PongCommand(Server *server) : Command(server) {

}

PongCommand::~PongCommand(void) {

}

void	PongCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.empty()) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "PING"));
		return ;
	}

	client->write(RPL_PING(client->getPrefix(), arguments.at(0)));

}
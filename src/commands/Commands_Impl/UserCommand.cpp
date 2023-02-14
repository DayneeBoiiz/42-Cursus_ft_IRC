/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:49:21 by sayar             #+#    #+#             */
/*   Updated: 2023/02/14 17:58:47 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/commands/Command.hpp"

UserCommand::UserCommand(Server *server, bool auth) : Command(server, auth) {

}

UserCommand::~UserCommand(void) {}

void UserCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (client->getState()) {
		client->reply(ERR_ALREADYREGISTRED(client->getNickName()));
		return ;
	}

	if (arguments.size() < 4) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "USER"));
		return ;
	}

	client->setUserName(arguments[0]);
	client->setRealName(arguments[3]);
	client->welcome();

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:08:01 by sayar             #+#    #+#             */
/*   Updated: 2023/02/14 17:33:38 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/commands/Command.hpp"

PassCommand::PassCommand(Server *server, bool auth) : Command(server, auth) {
}

PassCommand::~PassCommand(void) {}

void PassCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (client->getState()) {
		client->reply(ERR_ALREADYREGISTRED(client->getNickName()));
		return ;
	}

	if (arguments.empty()) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "PASS"));
		return ;
	}

	if (_server->getPassword() != arguments[0].substr(arguments[0][0] == ':' ? 1 : 0)) {
		client->reply(ERR_PASSWDMISMATCH(client->getNickName()));
		return ;
	}

	client->setState(LOGIN);

}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:03:08 by sayar             #+#    #+#             */
/*   Updated: 2023/02/14 17:18:39 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/commands/Command.hpp"

NickCommand::NickCommand(Server *server, bool auth) : Command(server, auth) {
}

NickCommand::~NickCommand(void) {}

void	NickCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.empty() || arguments[0].empty()) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "NICK"));
		return ;
	}

	std::string nick = arguments[0];
	if (_server->getClient(nick)) {
		client->reply(ERR_NICKNAMEINUSE(client->getNickName()));
		return ;
	}

	client->setNickName(nick);
	client->welcome();

}
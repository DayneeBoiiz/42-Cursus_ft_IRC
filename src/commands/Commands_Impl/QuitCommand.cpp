/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:49:49 by sayar             #+#    #+#             */
/*   Updated: 2023/02/17 22:09:21 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/commands/Command.hpp"

QuitCommand::QuitCommand(Server *server, bool auth) : Command(server, auth) {

}

QuitCommand::~QuitCommand(void) {

}

void	QuitCommand::execute(Client *client, std::vector<std::string> arguments) {

	std::string reason = arguments.empty() ? "Leaving..." : arguments.at(0);
	reason = reason.at(0) == ':' ? reason.substr(1) : reason;

	// for (std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); it++) {
	// 	if (arguments.size() > 2)
	// 		it++;
	// 	reason.append(" " + (*it));
	// }

	client->write(RPL_QUIT(client->getPrefix(), reason));
	// _server->DisconnectClient(client->getFD());

}
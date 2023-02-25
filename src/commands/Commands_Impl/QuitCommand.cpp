/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:49:49 by slammari          #+#    #+#             */
/*   Updated: 2023/02/25 18:43:13 by sayar            ###   ########.fr       */
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

	client->write(RPL_QUIT(client->getPrefix(), reason));
	_server->DisconnectClient(client->getFD());

}
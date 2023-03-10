/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NamesCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:35:25 by slammari          #+#    #+#             */
/*   Updated: 2023/02/28 19:31:38 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/commands/CommandHandler.hpp"

NamesCommand::NamesCommand(Server *server) : Command(server) {

}

NamesCommand::~NamesCommand(void) {

}

void	NamesCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.size() == 1) {

		std::string name = arguments[0];
		Channel *channel = _server->getChannel(name);

		if (!channel) {
			client->reply(ERR_NOSUCHCHANNEL(client->getNickName(), name));
			return ;
		}

    	std::string users;
    	std::vector<std::string> nicknames = channel->getNicknames();
    	for (std::vector<std::string>::iterator it = nicknames.begin(); it != nicknames.end(); it++)
			users.append(*it + " ");

    	client->reply(RPL_NAMREPLY(client->getNickName(), channel->getName(), users));
    	client->reply(RPL_ENDOFNAMES(client->getNickName(), channel->getName()));

	}
}
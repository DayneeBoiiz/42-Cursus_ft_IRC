/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:36:35 by sayar             #+#    #+#             */
/*   Updated: 2023/02/22 16:39:16 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/commands/Command.hpp"

TopicCommand::TopicCommand(Server *server) : Command(server) {

}

TopicCommand::~TopicCommand(void) {

}

void	TopicCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.size() <= 1) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "TOPIC"));
		return ;
	}

	

	if (arguments.size() == 1) {

	}

}
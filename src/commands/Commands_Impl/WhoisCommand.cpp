/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoisCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:05:10 by sayar             #+#    #+#             */
/*   Updated: 2023/02/24 11:05:12 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/commands/CommandHandler.hpp"

WhoisCommand::WhoisCommand(Server *server) :  Command(server)
{
}

WhoisCommand::~WhoisCommand(void)
{
}

void	WhoisCommand::execute(Client *client, std::vector<std::string> arguments)
{
    if (arguments.size() < 1) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "WHOIS"));
		return ;
	}

	std::string name = arguments[0];
	Client *_client = _server->getClient(name);
	 if (!_client)
	 {
		client->reply(ERR_NOSUCHNICK(client->getNickName(), name));
		return ;
	}
	client->reply(RPL_WHOIS(client->getRealName(), client->getNickName(), client->getUserName(), client->getHostName()));
	return;
}
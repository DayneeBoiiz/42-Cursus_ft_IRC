/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:45:11 by sayar             #+#    #+#             */
/*   Updated: 2023/02/15 20:55:57 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/commands/CommandHandler.hpp"

JoinCommand::JoinCommand(Server *server) :  Command(server)
{
}

JoinCommand::~JoinCommand(void)
{
}

void	JoinCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.empty()) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "PASS"));
		return;
	}

	std::string name = arguments[0];
	std::string password = arguments.size() > 1 ? arguments[1] : "";

	Channel *channel = client->getChannel();
	if (channel) {
		client->reply(ERR_TOOMANYCHANNELS(client->getNickName(), name));
		return;
	}

	channel = _server->getChannel(name);
	if (!channel)
		channel = _server->createChannel(name, password, client);

	if (channel->getMaxClients() > 0 && channel->getNumClients() >= channel->getMaxClients()){
		client->reply(ERR_CHANNELISFULL(client->getNickName(), name));
		return;
	}

	if (channel->getPassword() != password) {
		client->reply(ERR_BADCHANNELKEY(client->getNickName(), name));
		return;
	}

	client->join(channel);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:51:03 by slammari          #+#    #+#             */
/*   Updated: 2023/02/25 18:43:58 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/commands/CommandHandler.hpp"
# include "../../../includes/commands/Command.hpp"

PartCommand::PartCommand(Server *srever) : Command(srever)
{
}

PartCommand::~PartCommand(void) {}

void	PartCommand::execute(Client *client, std::vector<std::string> arguments)
{
    if(arguments.empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "PART"));
        return;
    }

    std::string name = arguments[0];

    Channel* channel = _server->getChannel(name);
    if(!channel)
    {
        client->reply(ERR_NOSUCHCHANNEL(client->getNickName(), name));
        return;
    }

    if(!client->getChannel() || client->getChannel()->getName() != name)
    {
        client->reply(ERR_NOTONCHANNEL(client->getNickName(), name));
        return;
    }

    client->leave();
}
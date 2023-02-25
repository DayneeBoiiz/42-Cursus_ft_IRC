/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 09:58:29 by sayar             #+#    #+#             */
/*   Updated: 2023/02/25 18:45:08 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDHANDLER_HPP
# define COMMANDHANDLER_HPP

class Command;

# include "../network/Channel.hpp"
# include "../network/Server.hpp"
# include "Command.hpp"
# include <map>

class CommandHandler {

private:
	Server							*_server;
	std::map<std::string, Command*>	_commands;

public:
	CommandHandler(Server *server);
	~CommandHandler(void);

	void	request(Client *client, std::string const &message);

};

#endif
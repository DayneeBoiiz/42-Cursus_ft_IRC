/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:24:13 by sayar             #+#    #+#             */
/*   Updated: 2023/02/11 15:53:59 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

class Server;

#include <string>
#include <numeric>
#include <regex>
#include "../network/Server.hpp"
#include "../network/Channel.hpp"

/*
**	JOIN Command
**	NICK Command
**	MODE Command
**	USER Command
**	PASS Command
**	PART Command
**	PING Command
**	PONG Command
**	KICK Command
**	QUIT Command
**	NOTICE Command
**	PRIVMSG Command
*/

class Command {

protected:
	Server	*_server;
	bool	_authRequired;

public:
	explicit Command(Server *server, bool authRequired = true) : _server(server), _authRequired(authRequired) {}
	virtual ~Command(void) {};

	bool authRequired(void) const {
		return (_authRequired);
	}

	virtual void execute(Client *client, std::vector<std::string> arguments) = 0;

};

class JoinCommand : public Command {

public:
	JoinCommand(Server *server);
	~JoinCommand(void);

	void	execute(Client *client, std::vector<std::string> arguments);
};

class NickCommand : public Command {

public:
	NickCommand(Server *server, bool auth);
	~NickCommand(void);

	void	execute(Client *client, std::vector<std::string> arguments);
};

class ModeCommand : public Command{
	
	public:
		ModeCommand(Server *server, bool auth);
		~ModeCommand(void);

		void	execute(Client *client, std::vector<std::string> arguments);
};

class UserCommand : public Command{
	
	public:
		UserCommand(Server *server, bool auth);
		~UserCommand(void);

		void	execute(Client *client, std::vector<std::string> arguments);
};

class PassCommand : public Command{

	public:
		PassCommand(Server *server, bool auth);
		~PassCommand(void);

		void	execute(Client *client, std::vector<std::string> arguments);
};

class PartCommand : public Command{

	public:
		PartCommand(Server *server, bool auth);
		~PartCommand(void);
		
		void	execute(Client *client, std::vector<std::string> arguments);
};

class PingCommand : public Command{

	public:
		PingCommand(Server *server, bool auth);
		~PingCommand(void);
		
		void	execute(Client *client, std::vector<std::string> arguments);
};

class PongCommand : public Command{

	public:
		PongCommand(Server *server, bool auth);
		~PongCommand(void);

		void	execute(Client *client, std::vector<std::string> arguments);
};

class PrivMCommand : public Command{

	public:
		PrivMCommand(Server *server, bool auth);
		~PrivMCommand(void);

		void	execute(Client *client, std::vector<std::string> arguments);
};

class QuitCommand : public command{

	public:
		QuitCommand(Server *server, bool auth);
		~QuitCommand(void);

		void	execute(Client *client, std::vector<std::string> arguments);
};

class UserCommand : public Command{
	
	public:
		UserCommand(Server *server, bool auth);
		~UserCommand(void);

		void	execute(Client *client, std::vector<std::string> arguments);
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:24:13 by sayar             #+#    #+#             */
/*   Updated: 2023/02/27 20:38:38 by slammari         ###   ########.fr       */
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
**	WHOIS Command
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
		ModeCommand(Server *server);
		~ModeCommand(void);

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
		PartCommand(Server *server);
		~PartCommand(void);
		
		void	execute(Client *client, std::vector<std::string> arguments);
};

class PingCommand : public Command{

	public:
		PingCommand(Server *server);
		~PingCommand(void);
		
		void	execute(Client *client, std::vector<std::string> arguments);
};

class PongCommand : public Command{

	public:
		PongCommand(Server *server);
		~PongCommand(void);

		void	execute(Client *client, std::vector<std::string> arguments);
};

class PrivMsgCommand : public Command{

	public:
		PrivMsgCommand(Server *server);
		~PrivMsgCommand(void);

		void	execute(Client *client, std::vector<std::string> arguments);
};

class QuitCommand : public Command{

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

class KickCommand : public Command{

	public:
		KickCommand(Server *server);
		~KickCommand(void);

		void	execute(Client *client, std::vector<std::string> arguments);
};

class NoticeCommand : public Command{
	
	public:
		NoticeCommand(Server *srver);
		~NoticeCommand(void);

		void	execute(Client *client, std::vector<std::string> arguments);
};

class WhoisCommand : public Command{
	
	public:
		WhoisCommand(Server *srver);
		~WhoisCommand(void);

		void	execute(Client *client, std::vector<std::string> arguments);
};

class NamesCommand : public Command {

	public:
		NamesCommand(Server *server);
		~NamesCommand(void);

		void	execute(Client *client, std::vector<std::string> arguments);

};


#endif

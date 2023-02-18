/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:06:54 by sayar             #+#    #+#             */
/*   Updated: 2023/02/18 12:03:11 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

class CommandHandler;

# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <cstring>
# include <unistd.h>
# include <fcntl.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <signal.h>
# include <map>
# include <vector>
# include <unistd.h>
# include <fcntl.h>
# include <poll.h>
# include <string.h>
# include "../Utils.hpp"
# include <errno.h>
# include <sstream>
# include "Client.hpp"
# include "Channel.hpp"
# include "../commands/CommandHandler.hpp"

# define MAX_CONNECTIONS 1000

class Server {

private:
	int						_sock;
	int						_running;
	const std::string		_host;
	const std::string		_port;
	const std::string		_password;
	std::vector<pollfd>		_pollfds;
	std::map<int, Client*>	_clients;
	std::vector<Channel*>	_channels;
	CommandHandler*			_commandHandler;

	typedef std::vector<pollfd>::iterator		pollfds_iterator;
	typedef std::map<int, Client*>::iterator	client_iterator;
	typedef std::vector<Channel*>::iterator		channel_iterator;


public:
	Server(const std::string &port, std::string const &password);
	~Server();

	int		newSocket(void);
	void	start(void);

	void	DisconnectClient(int fd);
	void	ConnectClient(void);
	void	MessageClient(int fd);
	void	RemoveChannel(Channel *channel);

	Channel	*getChannel(std::string const &name);
	Channel	*createChannel(std::string const &name, std::string const &password, Client *client);
	Client	*getClient(std::string const &nickname);

	std::string	readMessage(int fd);
	std::string getPassword(void) const;
};

#endif
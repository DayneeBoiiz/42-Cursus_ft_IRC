/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:06:54 by sayar             #+#    #+#             */
/*   Updated: 2023/01/07 19:26:38 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

class Client;

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

# define MAX_CONNECTIONS 1000

class Server {

private:
	int					_sock;
	int					_running;
	const std::string	_host;
	const std::string	_port;
	const std::string	_password;
	std::vector<pollfd>	_pollfds;
	std::map<int, Client*>	_client;

	typedef std::vector<pollfd>::iterator pollfds_iterator;


public:
	Server(const std::string &port, std::string const &password);
	~Server();

	int		newSocket(void);
	void	start(void);

	void	DisconnectClient(int fd);
	void	ConnectClient(void);
};

#endif
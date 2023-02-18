/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:26:16 by sayar             #+#    #+#             */
/*   Updated: 2023/02/18 16:58:38 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

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
# include <errno.h>
# include <sstream>
# include <stdexcept>
# include "Utils.hpp"
# include <thread>

class Bot {

private:
	std::string _host;
	std::string _port;
	std::string _password;

	int 		_sock;

public:
	Bot(std::string const &host, std::string const &port, std::string const password);
	~Bot(void);


	int		newSocket(void);
	void	start(void);
	void	authentication(void);
	void	send_to_client(std::string command);

	static void	ServerListener(Bot *bot);
	void	MessageRecieved(std::string const &message);
};

/* -------------------------------------------------------------------------- */
/*                                   COLORS                                   */
/* -------------------------------------------------------------------------- */
# define CC_BLK "\e[0;30m"
# define CC_RED "\e[0;31m"
# define CC_GRN "\e[0;32m"
# define CC_YEL "\e[0;33m"
# define CC_BLU "\e[0;34m"
# define CC_MAG "\e[0;35m"
# define CC_CYN "\e[0;36m"
# define CC_WHT "\e[0;37m"



#endif
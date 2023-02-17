/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:26:16 by sayar             #+#    #+#             */
/*   Updated: 2023/02/17 23:33:09 by sayar            ###   ########.fr       */
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

class Bot {

private:
	std::string _host;
	std::string _port;
	std::string _password;

	int 		_sock;

public:
	Bot(std::string const &host, std::string const &port, std::string const password);
	~Bot(void);


	int	newSocket(void);
};


#endif
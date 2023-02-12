/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:41:59 by sayar             #+#    #+#             */
/*   Updated: 2023/02/12 22:00:15 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Bot.hpp"

Bot::Bot(std::string const &host, std::string const &port, std::string const &password) :
	_port(port), _host(host), _password(password) {
		_socket = newSocket();
}

Bot::~Bot(void) {}

int	Bot::newSocket(void) {
	
}

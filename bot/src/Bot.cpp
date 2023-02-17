/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:41:59 by sayar             #+#    #+#             */
/*   Updated: 2023/02/17 23:33:19 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Bot.hpp"

Bot::Bot(std::string const &host, std::string const &port, std::string const password) :
	_host(host), _port(port), _password(password) {
		_sock = newSocket();
}

Bot::~Bot(void) {

}

int	Bot::newSocket(void) {

	

}
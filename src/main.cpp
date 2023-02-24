/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:17:35 by sayar             #+#    #+#             */
/*   Updated: 2023/02/24 15:18:58 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/network/Server.hpp"

int main(int ac, char **av) {

	try {

		if (ac != 3) {
			std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;;
			return (1);
		}

		Server main(av[1], av[2]);
		main.start();

	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}
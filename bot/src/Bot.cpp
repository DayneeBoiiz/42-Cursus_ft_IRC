/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:41:59 by sayar             #+#    #+#             */
/*   Updated: 2023/02/20 16:03:02 by sayar            ###   ########.fr       */
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

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		throw std::runtime_error("Error while opening socket...");
	}

	struct sockaddr_in	server_address = {};

	bzero((char *) &server_address, sizeof(server_address));

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(std::stoi(_port));
	server_address.sin_addr.s_addr = inet_addr(_host.c_str());

	if (connect(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
		throw std::runtime_error("Couldn't connect to host...");
	}

	return (sockfd);
}

void	Bot::send_to_client(std::string command) {

	std::cout << CC_RED << " [-] " << command << std::endl;

	std::string standard = command + "\r\n";
	if (send(_sock, standard.c_str(), standard.size(), 0) < 0) {
		throw std::runtime_error("Couldn't send command to client...");
	}
}

void	Bot::MessageRecieved(std::string const &message) {

	ft::s_vector arguments = ft::split(message);

	if (arguments.size() < 2) {
		return ;
	}

	std::string source = arguments.at(0);
	std::string	type = arguments.at(1);

	// std::cout << source << " " << std::endl;
	// std::cout << "---> " << type << " " << std::endl;

	if (std::atoi(type.c_str()) > 0) {
		if (arguments.size() < 3) {
			return ;
		}

		reply_numeric();
	}

}

void	Bot::ServerListener(Bot *bot) {

	char	buffer[256];
	int		len;

	while ((len = recv(bot->_sock, buffer, 256, 0)) > 0) {
		buffer[len] = 0;
		bot->MessageRecieved(std::string(buffer, len));
	}

	close(bot->_sock);

}

void	Bot::authentication(void) {

	send_to_client("PASS " + _password);
	send_to_client("NICK irc_bot");
	send_to_client("USER irc_bot 0 * :42 ft_irc's bot");

}

void	Bot::start(void) {

	authentication();

	std::thread thread(Bot::ServerListener, this);
	thread.detach();

	std::string input;
	std::getline(std::cin, input);

	while (input != "exit") {
		std::getline(std::cin, input);
	}

	send_to_client("QUIT:Bye, bye...");

}

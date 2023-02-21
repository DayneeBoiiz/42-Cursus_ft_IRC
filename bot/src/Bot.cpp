/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:41:59 by sayar             #+#    #+#             */
/*   Updated: 2023/02/21 14:22:25 by sayar            ###   ########.fr       */
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

	usleep(500);
	std::string standard = command + "\r\n";
	if (send(_sock, standard.c_str(), standard.size(), 0) < 0) {
		throw std::runtime_error("Couldn't send command to client...");
	}
}

void	Bot::sendPrivMessage(std::string const &source) {

	std::string replies[14] = { "PRIVMSG " + source + " :Reply(704): start miniIRC_server Help System",
								"PRIVMSG " + source + " :Reply(705): start",
								"PRIVMSG " + source + " :Reply(705): start This system provides help for commands and modes.",
								"PRIVMSG " + source + " :Reply(705): Available server commands:",
								"PRIVMSG " + source + " :Reply(705): /JOIN :Join a channel",
								"PRIVMSG " + source + " :Reply(705): /KICK :Kick a user from a channel",
								"PRIVMSG " + source + " :Reply(705): /MODE :change the mode of channel ['k','n','l']",
								"PRIVMSG " + source + " :Reply(705): /NICK :change the nickname on the server",
								"PRIVMSG " + source + " :Reply(705): /NOTICE :send a notice message to a user",
								"PRIVMSG " + source + " :Reply(705): /PART :leave a channel",
								"PRIVMSG " + source + " :Reply(705): /PASS :change the password",
								"PRIVMSG " + source + " :Reply(705): /PRIVMSG :send a private message to a user",
								"PRIVMSG " + source + " :Reply(705): /QUIT :quit the server",
								"PRIVMSG " + source + " :Reply(705): /USER :register in the server"};

	for (int i = 0; i < 14; i++) {
		send_to_client(replies[i]);
	}
}

void	Bot::sendPrivMessage(std::string const &source, std::string const &message) {
	send_to_client("PRIVMSG " + source + " :" + message);
}

void	Bot::reply_Command(std::string const &source, std::string const &command, std::vector<std::string> args) {

	std::string nickname = source;
	std::string::size_type pos = nickname.find('!');
	if (std::string::npos != pos) {
		nickname = nickname.substr(1, pos - 1);
	}

	std::cout << CC_GRN << " [+] (" << nickname << ") " << command << " " << ft::join(" ", args) << std::endl;

	if (command == "PRIVMSG") {

		if (args.size() >= 2 && args.at(1).substr(1) == "DRAWCARD") {

			std::string cards = "234567890JQKA";
			std::string suits = "HCSD";

			sendPrivMessage(nickname,
						ft::formatString("https://deckofcardsapi.com/static/img/%c%c.png",
										  cards[rand() % 13],
										  suits[rand() % 4]));
			return;
		}

		if (args.size() >= 2 && args.at(1).substr(1) == "HELP") {
			sendPrivMessage(nickname);
			return ;
		}

		sendPrivMessage(nickname, "Available Commands: 'DRAWCARD' 'SENDFILE' 'HELP' ");
		return ;
	}

}

void	Bot::reply_numeric(std::string const &source, std::string const &reply, std::vector<std::string> args) {

	(void) source;
	std::cout << std::endl;
	std::cout << CC_GRN << " [+] (" << reply << ") " << ft::join(" ", args) << std::endl;

}

void	Bot::MessageRecieved(std::string const &message) {

	ft::s_vector arguments = ft::split(message);

	if (arguments.size() < 2) {
		return ;
	}

	std::string source = arguments.at(0);
	std::string	type = arguments.at(1);

	if (atoi(type.c_str()) > 0) {
		if (arguments.size() < 3) {
			return ;
		}

		reply_numeric(source, type, ft::s_vector(arguments.begin() + 3, arguments.end()));
		return ;
	}

	reply_Command(source, type, ft::s_vector(arguments.begin() + 2, arguments.end()));

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:16:55 by sayar             #+#    #+#             */
/*   Updated: 2023/02/15 15:10:11 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/network/Server.hpp"

Server::Server(std::string const &port, std::string const &password) : _running(1), _host("127.0.0.1"),
	 _port(port), _password(password) {

	_sock = newSocket();
	_commandHandler = new CommandHandler(this);
}

Server::~Server(void) {
	delete _commandHandler;
}

void	Server::MessageClient(int fd) {

	try {
		Client *client = _clients.at(fd);
		_commandHandler->request(client, readMessage(fd));
	}
	catch (const std::out_of_range &e) {}

}

void	Server::DisconnectClient(int fd) {

	try {

		Client *client = _clients.at(fd);
		client->leave();

		char log[1000];
		sprintf(log, "%s:%d has disconnected...", client->getHostName().c_str(), client->getPort());
		ft_print_log(log);

		_clients.erase(fd);
		for (pollfds_iterator it = _pollfds.begin(); it != _pollfds.end(); it++) {
			if (it->fd != fd)
				continue ;
			_pollfds.erase(it);
			close(fd);
			break ;
		}
		delete client;
	}
	catch (const std::out_of_range &e) {}

}

void	Server::ConnectClient(void) {

	int fd;
	sockaddr_in s_addr = {};
	socklen_t	s_len = sizeof(s_addr);

	fd = accept(_sock, (struct sockaddr *)&s_addr, &s_len);
	if (fd < 0) {
		throw std::runtime_error("Error while accepting client connection...");
	}

	pollfd	pollfd = {fd, POLLIN, 0};
	_pollfds.push_back(pollfd);

	char hostname[NI_MAXHOST];
	if (getnameinfo((struct sockaddr *)&s_addr, sizeof(s_addr), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV) < 0) {
		throw std::runtime_error("Error while getting hostname on new client...");
	}

	Client *client = new Client(fd, ntohs(s_addr.sin_port), hostname);
	_clients.insert(std::make_pair(fd, client));

	char log[1000];
	sprintf(log, "%s:%d has connected", client->getHostName().c_str(), client->getPort());
	ft_print_log(log);

}

void	Server::start(void) {

	pollfd	server_fd = {_sock, POLLIN, 0};
	_pollfds.push_back(server_fd);
	int pid;

	ft_print_log("Server is listening...");

	while (_running) {

		// if (poll(_pollfds.begin().base(), _pollfds.size(), -1) < 0) {
		// 	throw std::runtime_error("Error while Polling from fd...");
		// }
		pid = poll(_pollfds.begin().base(), _pollfds.size(), -1);

		pollfds_iterator	it;
		for (it = _pollfds.begin(); it != _pollfds.end(); it++) {
			if (it->revents == 0)
				continue ;

			if ((it->revents & POLLHUP) == POLLHUP) {
				DisconnectClient(it->fd);
				break ;
			}

			if ((it->revents & POLLIN) == POLLIN) {
				if (it->fd == _sock) {
					ConnectClient();
					break ;
				}
				MessageClient(it->fd);
			}
		}

	}

}

int	Server::newSocket(void) {

	int	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		throw std::runtime_error("Error while opening socket...");
	}

	int value = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) < 0) {
		throw std::runtime_error("Error while setting socket options...");
	}

	if (fcntl(sockfd, F_SETFL, O_NONBLOCK) < 0) {
		throw std::runtime_error("Error while setting socket to NON_BLOCKING...");
	}

	struct sockaddr_in server_address = {};

	bzero((char *) &server_address, sizeof(server_address));

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(std::stoi(_port));

	if (bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
		throw std::runtime_error("Error while binding socket...");
	}

	if (listen(sockfd, MAX_CONNECTIONS) < 0) {
		throw std::runtime_error("Error while listening on socket...");
	}
	return (sockfd);
}

Channel	*Server::getChannel(std::string const &name) {

	for (channel_iterator it = _channels.begin() ; it != _channels.end(); it++) {
		if (it.operator*()->getName() == name) {
			return (it.operator*());
		}
	}
	return (NULL);
}

Channel	*Server::createChannel(std::string const &name, std::string const &password, Client *client) {

	Channel	*channel = new Channel(name, password, client);
	_channels.push_back(channel);

	return (channel);
}

Client	*Server::getClient(std::string const &nickname) {

	for (client_iterator it = _clients.begin(); it != _clients.end(); it++) {
		if (!nickname.compare(it->second->getNickName()))
			return (it->second);
	}
	return (NULL);
}

std::string Server::readMessage(int fd) {

	std::string msg;
	char buffer[100];

	bzero(buffer, 100);

	while (!std::strstr(buffer, "\r\n")) {

		bzero(buffer, 100);
		if (recv(fd, buffer, 100, 0) < 0) {
			if (errno != EWOULDBLOCK)
				throw std::runtime_error("Error while reading buffer from client");
		}
		msg.append(buffer);
	}
	return (msg);
}

std::string Server::getPassword(void) const {
	return (this->_password);
}

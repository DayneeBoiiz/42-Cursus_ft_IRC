/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:16:35 by sayar             #+#    #+#             */
/*   Updated: 2023/02/22 21:50:59 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/network/Channel.hpp"

Channel::Channel(Server *server, std::string const &name, std::string const &password, Client *admin) :
	_server(server), _name(name), _admin(admin), _k(password), _l(0), _n(false) {

}

Channel::~Channel(void) {}

void	Channel::broadcast(std::string const &message) {

	// std::cout << "------>  " << message << std::endl;
	for (client_iterator it = _clients.begin(); it != _clients.end(); it++) {
		(*it)->write(message);
	}
}

void	Channel::broadcast(std::string const &message, Client *out) {
	for (client_iterator it = _clients.begin(); it != _clients.end(); it++) {
		if ((*it) == out)
			continue ;
		(*it)->write(message);
	}
}

void	Channel::removeClient(Client *client) {

	if (_clients.size()) {
		_clients.erase(std::remove(_clients.begin(), _clients.end(), client), _clients.end());
	}
	client->setChannel(nullptr);

	if (_clients.empty()) {
		_server->RemoveChannel(this);
		return ;
	}

	if (_admin == client) {
		_admin = _clients.begin().operator*();

		char log[100];
		sprintf(log, "%s is now admin of channel %s.", _admin->getNickName().c_str(), _name.c_str());
		ft_print_log(log);
	}
}

void	Channel::kickClient(Client *client, Client *target, std::string const &reason) {
	broadcast(RPL_KICK(client->getPrefix(), _name, target->getNickName(), reason));
	removeClient(target);

	char log[100];
	sprintf(log, "%s kicked %s from channel %s.", client->getNickName().c_str(), target->getNickName().c_str(), _name.c_str());
	ft_print_log(log);
}

void	Channel::addClient(Client *client) {
	_clients.push_back(client);
}

Client	*Channel::getAdmin(void) const {
	return (this->_admin);
}

std::string Channel::getName() const {
	return (this->_name);
}

std::string Channel::getPassword() const {
	return (this->_k);
}

void	Channel::setPassword(std::string const &password) {
	this->_k = password;
}

size_t	Channel::getMaxClients(void) const {
	return (this->_l);
}

void	Channel::setMaxClient(size_t maxClient) {
	this->_l = maxClient;
}

bool	Channel::isExt(void) const {
	return (this->_n);
}

void	Channel::setExt(bool n) {
	this->_n = n;
}

size_t	Channel::getNumClients(void) const {
	return (_clients.size());
}

std::vector<std::string>	Channel::getNicknames(void) {
	std::vector<std::string> nicknames;

	for (client_iterator it = _clients.begin(); it != _clients.end(); it++) {
		Client *client = it.operator*();
		nicknames.push_back((_admin == client ? "@" : "") + (*it)->getNickName());
	}
	return (nicknames);
}

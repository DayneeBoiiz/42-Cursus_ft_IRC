/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:26:29 by schahid           #+#    #+#             */
/*   Updated: 2023/02/25 18:40:46 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/network/Client.hpp"

Client::Client(int fd_, int port_, std::string hostname_)
{
    this->fd = fd_;
    this->port = port_;
    this->hostname = hostname_;
    this->state = HANDSHAKE;
	this->channel = NULL;
}

void    Client::write(std::string const &message)
{
    std::string buffer = message + "\r\n";

    if (send(this->fd, buffer.c_str(), buffer.length(), 0) < 0) {
		throw std::runtime_error("Error while sending message to client");
	}
}

Client::~Client(void) {}

void    Client::reply(std::string const &message)
{
    write(":" + getPrefix() + " " + message);
}

void    Client::welcome(void)
{
    if (this->state != LOGIN || user_name.empty() || real_name.empty() || nick_name.empty())
        return ;
    this->state= PLAY;

    reply(RPL_WELCOME(nick_name));

	ft_print_log(this->getHostName() + ":" + std::to_string(this->getPort()) + " is known as " + this->getNickName());
}

void Client::join(Channel *channel)
{
    channel->addClient(this);
    this->channel = channel;
    std::string users;
    std::vector<std::string> nicknames = channel->getNicknames();
    for (std::vector<std::string>::iterator it = nicknames.begin(); it != nicknames.end(); it++)
		users = *it + " ";

    reply(RPL_NAMREPLY(nick_name, this->channel->getName(), users));
    reply(RPL_ENDOFNAMES(nick_name, this->channel->getName()));

	channel->broadcast(RPL_JOIN(nick_name, channel->getName()));

	ft_print_log(this->nick_name + " has joined the channel " + channel->getName());
}

void Client::leave(void)
{
    if (!channel) return;

	const std::string name = channel->getName();

	channel->broadcast(RPL_PART(getPrefix(), channel->getName()));
	channel->removeClient(this);

	ft_print_log(this->nick_name + " has left the channel " + name);
}

std::string Client::getPrefix(void) const
{
	std::string user = this->user_name;
    std::string host = this->hostname;

    if (user_name.empty())
        user = this->user_name;
    else
        user = "!" + this->user_name;
    if (hostname.empty())
        host = this->hostname;
    else
        host = "@" + this->hostname;
    return ( this->nick_name + user + host);
}

void	Client::setChannel(Channel *_channel) {
	this->channel = _channel;
}

Channel*  Client::getChannel(void) const
{
    return (this->channel);
}

std::string Client::getHostName(void) const
{
    return (this->hostname);
}

int Client::getFD(void) const
{
    return (this->fd);
}

int Client::getPort(void) const
{
    return (this->port);
}

std::string Client::getRealName(void) const
{
    return (this->real_name);
}

std::string Client::getNickName(void) const
{
    return (this->nick_name);
}

std::string Client::getUserName(void) const
{
    return (this->user_name);
}

int Client::getState(void) const
{
    return (this->state == PLAY);
}

void	Client::setNickName(std::string const &name) {
	this->nick_name = name;
}

void	Client::setState(int _state) {
	this->state = _state;
}

void	Client::setRealName(std::string const &name) {
	this->real_name = name;
}

void	Client::setUserName(std::string const &name) {
	this->user_name = name;
}

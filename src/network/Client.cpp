/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:26:29 by schahid           #+#    #+#             */
/*   Updated: 2023/02/14 17:58:00 by sayar            ###   ########.fr       */
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
    write (":" + getPrefix() + " " + message);
}

void    Client::welcome(void)
{
    if (this->state != LOGIN || user_name.empty() || real_name.empty() || nick_name.empty())
        return ;
    this->state= PLAY;

    reply(RPL_WELCOME(nick_name));

	char log[100];
	sprintf(log, "%s:%d is known as %s.", getHostName().c_str(), getPort(), getNickName().c_str());
	ft_print_log(log);
}

void Client::join(Channel *channel)
{
    channel->addClient(this);
    this->channel = channel;
    std::string users;
    std::vector<std::string> nicknames = channel->getNicknames();
    for (std::vector<std::string>::iterator it = nicknames.begin(); it != nicknames.end(); it++)
        users += " ";

    reply(RPL_NAMREPLY(nick_name, this->channel->getName(), users));
    reply(RPL_ENDOFNAMES(nick_name, this->channel->getName()));

	channel->broadcast(RPL_JOIN(nick_name, channel->getName()));

	char log[1000];
	sprintf(log, "%s has joined the channel %s", getNickName().c_str(), channel->getName().c_str());
    ft_print_log(log);
}

void Client::leave(void)
{
    this->channel->removeClient(this);
    ft_print_log(this->nick_name + "has left channel " + channel->getName());
}

std::string Client::getPrefix(void) const
{
	return (nick_name + (user_name.empty() ? "" : "!" + user_name) + (hostname.empty() ? "" : "@" + hostname));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:07:35 by sayar             #+#    #+#             */
/*   Updated: 2023/01/18 19:42:50 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANELL_HPP
# define CHANELL_HPP

class Client;

# include "Server.hpp"
# include "Channel.hpp"
# include "Client.hpp"

class Channel {

	typedef std::vector<Client*>::iterator	client_iterator;

private:
	std::string				_name;
	Client					*_admin;
	std::vector<Client*>	_clients;

	/* Channel Mods*/
	std::string				_k; /** set/remove the channel key (password) **/
	size_t					_l; /** set/remove the user limit to channel **/
	bool					_n; /** toggle the no messages to channel from clients on the outside **/

public:
	Channel(std::string const &name, std::string const &password, Client *admin);
	~Channel(void);

	Client*						getAdmin(void) const;
	std::string 				getName(void) const;
	std::string 				getPassword(void) const;
	size_t						getMaxClients(void) const;
	bool						isExt(void) const;
	size_t						getNumClients(void) const;
	std::vector<std::string>	getNicknames(void);

	void	setPassword(std::string const &password);
	void	setMaxClient(size_t maxClient);
	void	setExt(bool n);

	void	broadcast(std::string const &message);
	void	broadcast(std::string const &message, Client *out);
	void	removeClient(Client *client);
	void	addClient(Client *client);
	void	kickClient(Client *client, Client *target, std::string const &reason);
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:09:42 by schahid           #+#    #+#             */
/*   Updated: 2023/01/18 19:45:03 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

class Channel;

# include <iostream>
# include "Channel.hpp"
# include <deque>

# define HANDSHAKE 0
# define LOGIN 1
# define PLAY 2
# define DISCONNECTED 3

class Client
{
    private:
        int fd;
        int port;
        std::string hostname;
        Channel* channel;
        std::string real_name;
        std::string nick_name;
        std::string user_name;
        int state;

    public:
        Client(int fd_, int port_, std::string hostname_);
        ~Client();
        void setChannel(Channel *channel);
        void write(std::string const &message);
        void leave(void);
        void join(Channel *channel);
        void reply(std::string const &message);
        void welcome(void);
        std::string getPrefix(void) const;
        Channel*  getChannel(void) const;
        std::string getNickName(void) const;
        std::string getHostName(void) const;
        int         getPort(void) const;
        int         getFD(void) const;
        std::string getRealName(void) const;
        std::string getUserName(void) const;
        int         getState(void) const;

};

#endif
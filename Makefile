# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sayar <sayar@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 18:53:12 by sayar             #+#    #+#              #
#    Updated: 2023/02/14 19:44:51 by sayar            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CC = c++

FLAGS = -Wall -Werror -Wextra -std=c++98 -g -fsanitize=address

INC = 	includes/commands/CommandHandler.hpp\
		includes/commands/Command.hpp\
		includes/network/Channel.hpp\
		includes/network/Client.hpp\
		includes/network/Server.hpp\
		includes/Utils.hpp\

SRC =	src/main.cpp\
		src/Utils.cpp\
		src/commands/CommandHandler.cpp\
		src/commands/Commands_Impl/JoinCommand.cpp\
		src/commands/Commands_Impl/KickCommand.cpp\
		src/commands/Commands_Impl/ModeCommand.cpp\
		src/commands/Commands_Impl/NickCommand.cpp\
		src/commands/Commands_Impl/NoticeCommand.cpp\
		src/commands/Commands_Impl/PartCommand.cpp\
		src/commands/Commands_Impl/PassCommand.cpp\
		src/commands/Commands_Impl/PingCommand.cpp\
		src/commands/Commands_Impl/PongCommand.cpp\
		src/commands/Commands_Impl/PrivMsgcommand.cpp\
		src/commands/Commands_Impl/QuitCommand.cpp\
		src/commands/Commands_Impl/UserCommand.cpp\
		src/network/Channel.cpp\
		src/network/Server.cpp\
		src/network/Client.cpp\

PREFIX = ./obj/

OBJ = ${addprefix $(PREFIX), $(SRC:.cpp=.o)}

all : $(NAME)

.PHONY : all clean fclean re

$(PREFIX) :
	@mkdir -p $(PREFIX)
	@mkdir -p $(PREFIX)/src
	@mkdir -p $(PREFIX)/src/commands
	@mkdir -p $(PREFIX)/src/commands/Commands_Impl
	@mkdir -p $(PREFIX)/src/network

$(NAME) : $(PREFIX) ${OBJ} ${INC}
	${CC} ${FLAGS} ${OBJ} -o ${NAME}

$(PREFIX)%.o : %.cpp ${INC}
	$(CC) $(FLAGS) -c -o $@ $<

clean :
	rm -rf $(OBJ)
	@rm -rf $(PREFIX)

fclean : clean
	rm -rf $(NAME)

re : fclean all
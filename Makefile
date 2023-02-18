# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sayar <sayar@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 18:53:12 by sayar             #+#    #+#              #
#    Updated: 2023/02/18 17:14:37 by sayar            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

RED = \033[0;32m
NC = \033[0m

CC = c++

FLAGS = -Wall -Werror -Wextra -std=c++98 -g

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
		src/commands/Commands_Impl/PrivMsgCommand.cpp\
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
	@mkdir -p $(PREFIX)/bot
	@mkdir -p $(PREFIX)/bot/src

$(NAME) : $(PREFIX) ${OBJ} ${INC}
	@${CC} ${FLAGS} ${OBJ} -o ${NAME}
	@printf "${RED}Server Created${NC}\n"

$(PREFIX)%.o : %.cpp ${INC}
	@$(CC) $(FLAGS) -c -o $@ $<

clean :
	rm -rf $(OBJ)
	@rm -rf $(PREFIX)

run : re
	./$(NAME) 9000 E056DF6899

fclean : clean
	rm -rf $(NAME)

re : fclean all
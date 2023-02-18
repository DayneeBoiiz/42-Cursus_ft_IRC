# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sayar <sayar@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 18:53:12 by sayar             #+#    #+#              #
#    Updated: 2023/02/18 13:14:16 by sayar            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

NAME_B = Bot

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

INC_B = bot/includes/Bot.hpp\

SRC_B =	bot/src/main.cpp\
		bot/src/Bot.cpp\

PREFIX = ./obj/

OBJ = ${addprefix $(PREFIX), $(SRC:.cpp=.o)}

OBJ_B = ${addprefix $(PREFIX), $(SRC_B:.cpp=.o)

all : $(NAME)

.PHONY : all clean fclean re

bonus : $(NAME_B)

$(PREFIX) :
	@mkdir -p $(PREFIX)
	@mkdir -p $(PREFIX)/src
	@mkdir -p $(PREFIX)/src/commands
	@mkdir -p $(PREFIX)/src/commands/Commands_Impl
	@mkdir -p $(PREFIX)/src/network
	@mkdir -p $(PREFIX)/bonus
	@mkdir -p $(PREFIX)/bonus/src

$(NAME_B) : $(PREFIX) ${OBJ_B} ${INC_B}
	${CC} ${FLAGS} ${OBJ_B} -o ${NAME_B}

$(NAME) : $(PREFIX) ${OBJ} ${INC}
	${CC} ${FLAGS} ${OBJ} -o ${NAME}

$(PREFIX)%.o : %.cpp ${INC}
	$(CC) $(FLAGS) -c -o $@ $<

clean :
	rm -rf $(OBJ)
	rm -rf $(OBJ_B)
	@rm -rf $(PREFIX)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(NAME_B)

re : fclean all
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sayar <sayar@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/18 17:01:47 by sayar             #+#    #+#              #
#    Updated: 2023/02/20 18:48:04 by sayar            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = IrcBot

RED = \033[0;32m
NC = \033[0m

CC = c++

FLAGS = -Wall -Werror -Wextra -g

INC =	includes/Bot.hpp\
		includes/Utils.hpp\

SRC =	src/main.cpp\
		src/Bot.cpp\

PREFIX = ./obj/

OBJ = ${addprefix $(PREFIX), $(SRC:.cpp=.o)}

all : $(NAME)

.PHONY : all clean fclean re

$(PREFIX) :
	@mkdir -p $(PREFIX)
	@mkdir -p $(PREFIX)/src

$(NAME) : $(PREFIX) ${OBJ} ${INC}
	@${CC} ${FLAGS} ${OBJ} -o ${NAME}
	@printf "${RED}Bot Created${NC}\n"

$(PREFIX)%.o : %.cpp ${INC}
	@$(CC) $(FLAGS) -c -o $@ $<

clean :
	rm -rf $(OBJ)
	@rm -rf $(PREFIX)

run : re
	./$(NAME) 127.0.0.1 9000 E056DF6899

fclean : clean
	rm -rf $(NAME)

re : fclean all
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/21 18:49:23 by chly-huc          #+#    #+#              #
#    Updated: 2021/01/23 14:04:48 by jsilance         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c path.c built_in.c exit.c handle_env.c utils.c ft_struct_env.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \


HEADERS =	minish.h
NAME = 		minishell
OBJ = 		${SRCS:.c=.o}
LIB =		libft.a
FLAGS =		-Wall -Wextra -Werror

%.c: %.o:
			@gcc -c -o $@ $?
			# @gcc -g ${FLAGS} -I ${HEADERS} -c $^ -o ${<:.c=.o}

$(NAME) : $(OBJ)
	@gcc -g $(OBJ) ${LIB} -o $(NAME)
	@echo "[Done !]"

all:		${NAME}
	
clean:	
			@rm -f ${OBJ}

fclean:		clean
			@rm -f Minishell

re:			fclean all

test:		re clean
			./${NAME}

.PHONY : fclean all re clean test
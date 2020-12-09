# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/21 18:49:23 by chly-huc          #+#    #+#              #
#    Updated: 2020/12/08 13:37:35 by chly-huc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS   = main.c path.c built_in.c exit.c handle_env.c utils.c ft_struct_env.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \


HEADERS =	minish.h
NAME = 		Minishell
OBJS = 		${SRCS:.c=.o}
LIB = libft.a
CC = gcc

.c.o:
			@${CC} -g ${FLAGS} -I ${HEADERS} -c $^ -o ${<:.c=.o}

$(NAME) : $(OBJS)
	@${CC} -g $(OBJS) ${LIB} -o $(NAME)
	@echo "[Done !]"


all:		${NAME}
	
clean:	
			@rm -f ${OBJS} ${OBJS}


fclean:		clean
			@rm -f Minishell


clarify:
			@rm -f ${OBJS}

re:			fclean all clarify


.PHONY : fclean all re clean clarify
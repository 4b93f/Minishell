# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/21 18:49:23 by chly-huc          #+#    #+#              #
#    Updated: 2021/01/23 20:44:10 by jsilance         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	env_cl/ft_envlstadd_back.c env_cl/ft_envlstadd_front.c \
		env_cl/ft_envlstclear.c env_cl/ft_envlstdelone.c env_cl/ft_envlstiter.c \
		env_cl/ft_envlstlast.c env_cl/ft_envlstnew.c env_cl/ft_envlstsize.c \
		main.c path.c built_in.c exit.c handle_env.c utils.c ft_struct_env.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		cmd_cl/ft_cmdlstadd_back.c cmd_cl/ft_cmdlstadd_front.c \
		cmd_cl/ft_cmdlstclear.c	cmd_cl/ft_cmdlstdelone.c cmd_cl/ft_cmdlstiter.c \
		cmd_cl/ft_cmdlstlast.c cmd_cl/ft_cmdlstnew.c cmd_cl/ft_cmdlstsize.c \
		lexer/main_lexer.c \
		parser/main_parser.c \
		
HEADERS =	minishell.h cmd_cl/ft_cmd_cl.h
NAME = 		minishell
OBJ = 		${SRCS:.c=.o}
LIB =		libft.a
FLAGS =		-Wall -Wextra -Werror

# .c .o:
%.o: %.c
			@gcc -c -o $@ $?
			# @gcc -g ${FLAGS} -I ${HEADERS} -c $^ -o ${<:.c=.o}

$(NAME): ${OBJ}
	@gcc ${FLAGS} ${OBJ} ${LIB} -o ${NAME}
	# @gcc -g $(OBJ) ${LIB} -o $(NAME)
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
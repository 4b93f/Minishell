# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/21 18:49:23 by chly-huc          #+#    #+#              #
#    Updated: 2021/03/20 21:00:18 by chly-huc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ENV_CL =	env_cl/ft_envlstadd_back.c env_cl/ft_envlstadd_front.c \
			env_cl/ft_envlstclear.c env_cl/ft_envlstdelone.c env_cl/ft_envlstiter.c \
			env_cl/ft_envlstlast.c env_cl/ft_envlstnew.c env_cl/ft_envlstsize.c \
		
CMD_CL =	cmd_cl/ft_cmdlstadd_back.c cmd_cl/ft_cmdlstadd_front.c \
			cmd_cl/ft_cmdlstclear.c cmd_cl/ft_cmdlstdelone.c cmd_cl/ft_cmdlstiter.c \
			cmd_cl/ft_cmdlstlast.c cmd_cl/ft_cmdlstnew.c cmd_cl/ft_cmdlstsize.c \

ROOT =		main.c path.c utils.c utils2.c \

ENV_U =		env_utils/ft_struct_env.c \

GNL =		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \

LEXER =		lexer/main_lexer.c \

PARSER =	parser/main_parser.c parser/pipe_n_read.c parser/parser_utils.c \

LIBFT =		libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c \
			libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_memccpy.c libft/ft_memchr.c \
			libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c libft/ft_strchr.c \
			libft/ft_strdup.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strncmp.c \
			libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_tolower.c libft/ft_toupper.c libft/ft_substr.c \
			libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c libft/ft_strmapi.c \
			libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c \
			libft/ft_strcmp.c libft/ft_lstnew.c libft/ft_lstadd_front.c libft/ft_lstsize.c \
			libft/ft_lstadd_back.c libft/ft_lstdelone.c libft/ft_lstclear.c libft/ft_lstiter.c \
			libft/ft_lstlast.c \

EXECUTOR =	executor/executor.c executor/exec_utils.c executor/exec_utils2.c executor/exec_utils3.c \
			executor/export.c executor/cd.c executor/echo.c executor/unset.c executor/exit.c \
			executor/exec_cmd.c executor/pwd.c \

EX_FREE =	ex_free/free_utils.c

SRCS =	$(EXECUTOR) $(LIBFT) $(PARSER) $(LEXER) $(GNL) $(EX_FREE) $(ENV_U) \
		$(ROOT) $(ENV_CL) $(CMD_CL) \
		
HEADERS =	minishell.h cmd_cl/ft_cmd_cl.h executor/executor.h structs.h \
			get_next_line/get_next_line.h

NAME = 		minishell

OBJ = 		${SRCS:.c=.o}

 FLAGS =		-Wall -Wextra -Werror -g3 -fsanitize=address
#FLAGS =		-Wall -Wextra -Werror -g3

%.o: %.c
			@gcc -c -g3 -o $@ $?

$(NAME): ${OBJ}
			@gcc -g3  -ltermcap -lncurses ${FLAGS} ${OBJ} -o ${NAME}
			@echo "[Done !]"

all:		${NAME}
	
clean:	
			@echo "Cleaning..."
			@/bin/rm -f ${OBJ}
			@echo "Cleaning complete!"

fclean:		clean
			@rm -f minishell

re:			fclean all

test:		re clean
			./${NAME}

.PHONY : fclean all re clean test

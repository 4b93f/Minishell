# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 21:51:32 by chly-huc          #+#    #+#              #
#    Updated: 2021/01/23 13:53:55 by jsilance         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS   = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c \
ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
ft_lstiter.c ft_lstlast.c \

HEADERS =	libft.h
NAME = 		libft.a
OBJ = 		${SRCS:.c=.o}

.c.o:
			@${CC} ${CFLAGS} -I ${HEADERS} -c $^ -o ${<:.c=.o}

${NAME}: 	${OBJ}
			@ar rc ${NAME} ${OBJ}

all:		${NAME}
	
clean:	
			@rm -f ${OBJ}

fclean:		clean
			@rm -f ${NAME} ${OBJ}

clarify:	clean

re:			fclean all

.PHONY : fclean all re clean
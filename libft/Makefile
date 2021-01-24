# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 21:51:32 by chly-huc          #+#    #+#              #
#    Updated: 2021/01/23 21:54:15 by jsilance         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS   = libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c \
libft/ft_isdigit.c libft/ft_isprint.c libft/ft_memccpy.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c \
libft/ft_memmove.c libft/ft_memset.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strlcat.c libft/ft_strlcpy.c \
libft/ft_strlen.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_tolower.c libft/ft_toupper.c \
libft/ft_substr.c libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c libft/ft_strmapi.c \
libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_strcmp.c \
libft/ft_lstnew.c libft/ft_lstadd_front.c libft/ft_lstsize.c \
libft/ft_lstadd_back.c libft/ft_lstdelone.c libft/ft_lstclear.c \
libft/ft_lstiter.c libft/ft_\lstlast.c \

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
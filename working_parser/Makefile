NAME=parser
SRC= parsing.c ft_split.c ft_strdup.c ft_strlen.c ft_strtrim.c ft_strjoin.c ft_strcpy.c
OBJ= $(SRC:.c=.o)
CC= gcc
INC = .
CFLAGS= -Wall -Wextra -Werror
RM= rm -f

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INC) $< -c -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)


clean:
	@$(RM) $(OBJ)

fclean: clean
	@echo "Removing binary file"
	@$(RM) $(NAME)

re: fclean all

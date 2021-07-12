ENV_SRC = env/env_lstaddback.c env/env_lstaddfront.c env/env_lstclear.c env/env_lstdelone.c env/env_lstiter.c env/env_lstlast.c env/env_lstnew.c env/env_lstsize.c \

CMD_SRC = cmd/cmd_lstaddback.c cmd/cmd_lstaddfront.c cmd/cmd_lstclear.c cmd/cmd_lstdelone.c cmd/cmd_lstiter.c cmd/cmd_lstlast.c cmd/cmd_lstnew.c cmd/cmd_lstsize.c \

GNL_SRC = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \

MAIN_SRC = main.c utils.c \

LIB = libft/libft.a \

ALL_SRCS = $(ENV_SRC) $(CMD_SRC) $(SRC) $(GNL_SRC) $(MAIN_SRC) \

OBJ = $(ALL_SRCS:.c=.o) \

INC = . \

CFLAGS= -Wall -Wextra -Werror \

CC = gcc \

RM = rm -f

HEADERS = parser.h struct/struct.h libft/libft.h get_next_line/get_next_line.h cmd/cmd.h env/env.h \

NAME = minishell

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INC) $< -c -o $@

$(NAME): $(OBJ)
	@echo "[Libft compilation...]"
	@$(MAKE) -C ./libft
	@$(MAKE) bonus -C ./libft
	$(CC) -g3 $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)


clean:
	@$(RM) $(OBJ)

fclean: clean
	@echo "Removing binary file"
	@$(RM) $(NAME)

re: fclean all
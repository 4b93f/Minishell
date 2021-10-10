MAIN_SRC = main.c utils.c utils2.c utils3.c parsing/strtolst.c struct/ft_struct_sh.c parsing/dollarz.c \
parsing/quote.c builtin/echo.c engine/start.c parsing/handling_red.c\
builtin/env.c builtin/pwd.c ex_free/ex_free.c builtin/exit.c builtin/export.c \
builtin/unset.c builtin/cd.c builtin/exec_cmd.c engine/exit_code.c parsing/pipe_n_red.c error/error.c \
engine/engine.c \

CMD_SRC = cmd/cmd_lstaddback.c cmd/cmd_lstaddfront.c cmd/cmd_lstclear.c cmd/cmd_lstdelone.c \
cmd/cmd_lstiter.c cmd/cmd_lstlast.c cmd/cmd_lstnew.c cmd/cmd_lstsize.c cmd/cmd.c cmd/cmd_utils.c\

ENV_SRC = env/env_lstaddback.c env/env_lstaddfront.c env/env_lstclear.c env/env_lstdelone.c \
env/env_lstiter.c env/env_lstlast.c env/env_lstnew.c \
env/env_lstsize.c env/env_lst_utils.c env/env_lst_utils2.c env/env.c \

LIB = lib/libft/libft.a \

ALL_SRCS = $(MAIN_SRC) $(ENV_SRC) $(CMD_SRC) \

OBJ = $(ALL_SRCS:.c=.o) \

INC = . \

CFLAGS= -Wall -Werror -Wextra -I /Users/chly-huc/.brew/opt/readline/include

CC = gcc \

RM = rm -rf

HEADERS = -I struct -I cmd -I env -I lib/libft \

NAME = minishell

all: $(NAME)

%.o: %.c
	@gcc -g3 $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "[Libft compilation...]"
	make -C lib/libft
	make bonus -C lib/libft
	@echo "[Minishell compilation...]"
	$(CC) -g3 -fsanitize=address $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) $(HEADERS) -L /Users/chly-huc/.brew/opt/readline/lib -lreadline


clean:
	@$(RM) $(OBJ)

fclean: clean
	@echo "Removing binary file"
	@$(RM) $(NAME)
	@$(MAKE) fclean -C lib/libft
	
re: fclean all
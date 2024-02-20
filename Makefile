MAIN_SRC = srcs/minishell.c srcs/utils.c srcs/utils2.c srcs/utils3.c srcs/parsing/strtolst.c srcs/struct/ft_struct_sh.c srcs/parsing/dollarz.c srcs/parsing/dollarz2.c\
srcs/parsing/quote.c srcs/builtin/echo.c srcs/engine/start.c srcs/parsing/handling_red.c srcs/parsing/handling_red2.c \
srcs/builtin/env.c srcs/builtin/pwd.c srcs/ex_free/ex_free.c srcs/builtin/exit.c srcs/builtin/export.c \
srcs/builtin/unset.c srcs/builtin/cd.c srcs/builtin/exec_cmd.c srcs/engine/exit_code.c srcs/parsing/pipe_n_red.c srcs/error/error.c \
srcs/engine/engine.c \

CMD_SRC = srcs/cmd/cmd_lstaddback.c srcs/cmd/cmd_lstaddfront.c srcs/cmd/cmd_lstclear.c srcs/cmd/cmd_lstdelone.c \
srcs/cmd/cmd_lstiter.c srcs/cmd/cmd_lstlast.c srcs/cmd/cmd_lstnew.c srcs/cmd/cmd_lstsize.c srcs/cmd/cmd.c srcs/cmd/cmd_utils.c\

ENV_SRC = srcs/env/env_lstaddback.c srcs/env/env_lstaddfront.c srcs/env/env_lstclear.c srcs/env/env_lstdelone.c \
srcs/env/env_lstiter.c srcs/env/env_lstlast.c srcs/env/env_lstnew.c \
srcs/env/env_lstsize.c srcs/env/env_lst_utils.c srcs/env/env_lst_utils2.c srcs/env/env.c \

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
	$(CC) -g3 $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) $(HEADERS) -L /Users/chly-huc/.brew/opt/readline/lib -lreadline


clean:
	@$(RM) $(OBJ)

fclean: clean
	@echo "Removing binary file"
	@$(RM) $(NAME)
	@$(MAKE) fclean -C lib/libft
	
re: fclean all
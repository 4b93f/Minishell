/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:15:25 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/12 18:21:45 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <stdio.h>
# include "errno.h"
# include "limits.h"
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../../lib/libft/libft.h"

# define ARG 6
# define CMD 7
# define FORK 1
# define UNV_ID 3
# define PIPE 666 
# define LEFT 888
# define RIGHT 555
# define DLEFT 999
# define DRIGHT 777
# define EXIT_ARG 4
# define PERM_DENIED 13
# define CMD_NOT_FOND 2
# define SYNTAX_ERROR 5
# define IS_DIRECTORY 21
# define EXIT_CHAR 12

enum e_boolean
{
	FALSE = 0,
	TRUE
};

typedef struct s_lst_cmd
{
	char	*cmd;

	int		type;
	void	*next;
	int		redirected;
}				t_lst_cmd;

typedef struct s_lst_env
{
	char		*var;
	void		*next;
	void		*content;
}				t_lst_env;

typedef struct s_sh
{
	int			ret;
	char		*dup;
	int			stat;
	int			fd_in;
	int			flag_n;
	int			ctrl_c;
	int			fd_out;
	t_lst_cmd	*lst_cmd;
	t_lst_cmd	*ptr_cmd;
	t_lst_env	*lst_env;
	t_lst_env	*ptr_env;
	int			**fd_pipe;
	char		*free_ptr;
	pid_t		child_pid;
	int			exit_code;
	int			block_cmd;
	char		*input_str;
	char		**all_path;
	int			fd_backup[2];
}				t_sh;

void		ft_pwd(void);
int			is_sep(int c);
void		sigret(int c);
void		ft_cd(t_sh *sh);
void		start(t_sh *sh);
void		quoting(t_sh *sh);
void		sh_free(t_sh *sh);
void		ft_echo(t_sh *sh);
void		ft_unset(t_sh *sh);
int			str_sep(char *str);
t_lst_cmd	*new_lst(t_sh *sh);
void		get_type(t_sh *sh);
void		ft_exit(t_sh *sh);
void		print_env(t_sh *sh);
int			red_error(t_sh *sh);
t_sh		*ft_malloc_sh(void);
void		ft_export(t_sh *sh);
void		ft_free_sh(t_sh *sh);
void		pipe_n_red(t_sh *sh);
int			ver_quote(char *str);
void		ft_free_env(t_sh *sh);
int			str_isdigit(char *str);
int			str_spechar(char *str);
void		get_all_path(t_sh *sh);
char		*get_actual_path(void);
void		setup_engine(t_sh *sh);
char		*dollar_cut(char *str);
char		*dollar_pass(char *str);
t_lst_cmd	*next_sep(t_lst_cmd *ptr);
int			get_redir_number(t_sh *sh);
t_lst_cmd	*next_sep2(t_lst_cmd *ptr);
int			error(t_sh *sh, char *str);
t_lst_cmd	*next_sep2(t_lst_cmd *ptr);
t_lst_cmd	*next_token(t_lst_cmd *ptr);
int			cmd_lstsize(t_lst_cmd *lst);
int			env_lstsize(t_lst_env *lst);
t_lst_env	*env_lstlast(t_lst_env *lst);
char		**lst_to_tab(t_lst_env *lst);
t_lst_cmd	*cmd_lstlast(t_lst_cmd *lst);
void		ft_print_lst(t_lst_cmd *lst);
void		exit_code(t_sh *sh, int nbr);
char		*dollarz(t_sh *sh, char *str);
void		env_lstdel(t_sh *sh, char *str);
void		env_setup(t_sh *sh, char **env);
void		exec(t_sh *sh, t_lst_cmd *token);
char		*ft_remove_char(char *str, int c);
void		go_end(t_sh *sh, t_lst_cmd *token);
void		print_export(t_sh *sh, char **tab);
char		*dollarz_value(t_sh *sh, char *str);
t_lst_cmd	*prev_sep(t_sh *sh, t_lst_cmd *ptr);
char		*env_lstcontent(t_sh *sh, char *str);
char		*ft_search_path(t_sh *sh, char *str);
void		red_left(t_sh *sh, t_lst_cmd *token);
t_lst_env	*env_lstnew(void *var, void *content);
int			index_token(t_sh *sh, t_lst_cmd *ptr);
void		red_right(t_sh *sh, t_lst_cmd *token);
t_lst_cmd	*prev_token(t_sh *sh, t_lst_cmd *ptr);
void		type(t_lst_cmd *cmd, t_lst_cmd *prev);
int			index_token(t_sh *sh, t_lst_cmd *ptr);
void		red_dleft(t_sh *sh, t_lst_cmd *token);
int			heredoc(t_sh *sh, char **tmp, int *fd);
void		red_dright(t_sh *sh, t_lst_cmd *token);
char		**malloc_tab(int size, t_lst_cmd *lst);
t_lst_cmd	*previous_sep(t_sh *sh, t_lst_cmd *ptr);
int			previous_type(t_sh *sh, t_lst_cmd *ptr);
t_lst_cmd	*previous_sep(t_sh *sh, t_lst_cmd *ptr);
void		red_forked(t_sh *sh, int pid, char *tmp);
t_lst_env	*env_lstfinder(t_lst_env *lst, char *var);
void		ft_sort_export(t_sh *sh, int i, char *tmp);
void		str_tolst(char *str, t_sh *sh, int i, int j);
int			env_lstdupe(t_sh *sh, char *var, char *value);
void		env_lstedit(t_sh *sh, char *var, char *value);
void		cmd_lstiter(t_lst_cmd *lst, void (*f)(void *));
void		env_lstiter(t_lst_env *lst, void (*f)(void *));
void		cmd_lstaddback(t_lst_cmd **alst, t_lst_cmd *new);
void		env_lstaddback(t_lst_env **alst, t_lst_env *new);
void		cmd_lstdelone(t_lst_cmd *lst, void (*del)(void*));
void		cmd_lstclear(t_lst_cmd **lst, void (*del)(void*));
void		cmd_lstaddfront(t_lst_cmd **alst, t_lst_cmd *new);
void		env_lstclear(t_lst_env **lst, void (*del)(void*));
void		env_lstdelone(t_lst_env *lst, void (*del)(void*));
void		env_lstadd_front(t_lst_env **alst, t_lst_env *new);
t_lst_cmd	*cmd_lstnew(void *content, int type, int redirected);
void		env_tolst(char **env, t_sh *sh, int i, int equal_pos);
void		exec_cmd(t_sh *sh, char *file, char **envp, char **argp);
void		is_quote_open(char *str, int *squote, int *dquote, int i);

#endif

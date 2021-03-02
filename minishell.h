/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:05:21 by chly-huc          #+#    #+#             */
/*   Updated: 2021/03/02 18:44:38 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H

# define MAIN_H

# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "env_cl/ft_env_cl.h"
# include "cmd_cl/ft_cmd_cl.h"
# include <stdio.h>
# include "get_next_line/get_next_line_bonus.h"
# include <math.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>

#define PERM_DENIED 13

enum		e_print_error
{
	SYNTAX_ERROR,
	NOT_VALID_ID,
	NO_SUCH_FILE
};

enum		e_token
{
	PIPE = 1,
	S_RIGHT_RED,
	D_RIGHT_RED,
	S_LEFT_RED
};

enum		e_cmd
{
	OTHER = -1,
	EXIT,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV
};

enum		e_error
{
	MALLOC_ERROR,
	EXIT_TO_MANY_ARG,
	EXIT_ILLEGAL,
	EXIT_NUM,
	PIPE_ERROR,
	ECHO_SYNTAX,
};

enum		e_stat
{
	PERM,
	IS_DIR
};

typedef struct	s_env_lst
{
	char		*var;
	void		*content;
	
	void		*next;
}				t_env_lst;

typedef struct	s_cmd_lst
{
	int			cmd_index;
	char		*cmd_str;
	char		*flags;

	int			pipe_in;
	int			fd_pipe_in;

	int			pipe_out;
	int			fd_pipe_out;
	t_list		*red_file;

	t_list		*str;
	
	int			pid;
	
	void		*next;
}				t_cmd_lst;

typedef struct	s_parser
{
	int			piped[2];
	t_list		*ptr_lst;
	t_cmd_lst	*ptr_cmd;
}				t_parser;

typedef struct	s_sh
{
	char **all_path; //--> liste chainee

	char		*input_str;
	char		**exec_env;
	char 		*save_str;
	int			flag_c;
	t_parser	parser;
	t_list		*arg_lst;
	t_cmd_lst	*cmd;
	t_env_lst	*env_lst;
	

}				t_sh;


t_sh		*ft_malloc_sh();
int			tablen(char **tab);
int			sort_export(t_sh *sh, int i, int j, int len);
char		**ft_realloc(char **str, char *line);
char		**tabcpy(char **tab);
char		*ft_strjoinfree(const char *s1, const char *s2);
char		**delete_env(t_sh *sh, char *delete_env, int len);
char		*get_actual_path(void);
void		*free_tab(char **tab);
void		print_tab(char **str);
void		last_cmd(t_sh *sh);
char		**lst_db_tab(t_cmd_lst *cmd);
void		print_env(t_env_lst *lst, int fd, t_sh *sh);
void		get_pwd(t_sh *sh);
void		create_env(t_sh *sh, char *new_env);
int			ft_error_stat(int ret, t_sh *sh);
int			ft_stat(char *filename, t_sh *sh);
void		get_all_path(t_sh *sh);
void		exec_cmd(t_cmd_lst *cmd, t_sh *sh);
void		ft_export(t_cmd_lst *cmd, t_sh *sh);
void		cd_info(t_sh *sh, int num, char *path);
void		ft_unset(t_cmd_lst *cmd, t_sh *sh);
void		ft_pwd(t_cmd_lst *cmd, t_sh *sh);
int			ft_isspace(int c);
void		strtolst(t_sh *t);
void		parser(t_sh *t);
t_env_lst	*env_lst_finder(t_env_lst *lst, char *var);
void		sh_free(t_sh *sh);
void		ft_error(int ret, t_sh *sh, int ext);
char		*ft_search_path(t_sh *sh, t_cmd_lst *cmd);
void		ft_free_sh(t_sh *sh);
char		*rm_guim(char *ptr);
void		ft_exit(t_cmd_lst *cmd, t_sh *sh);
int			ft_print_error(int ret, char *str);

int			executor(t_sh *sh);
int			set_pipe_red(t_sh *sh);
int			sep_checker(char *str);
int			lex_to_cmdstr(t_sh *sh);
char		*ft_backslash(char *s1);

void		ft_set_free_env(t_sh *sh, void *var, void *content);
void		ft_portal(t_sh *sh, int ret, int pid, int fd[2]);

void		ft_env_lstadd_back(t_env_lst **alst, t_env_lst *new);
void		ft_env_lstadd_front(t_env_lst **alst, t_env_lst *new);
void		ft_env_lstclear(t_env_lst **lst, void (*del)(void*));
void		ft_env_lstdelone(t_env_lst *lst, void (*del)(void*));
void		ft_env_lstiter(t_env_lst *lst, void (*f)(void *));
t_env_lst	*ft_env_lstlast(t_env_lst *lst);
t_env_lst	*ft_env_lstnew(void *var, void *content);
int			ft_env_lstsize(t_env_lst *lst);

void		ft_cmd_lstadd_back(t_cmd_lst **alst, t_cmd_lst *new);
void		ft_cmd_lstadd_front(t_cmd_lst **alst, t_cmd_lst *new);
void		ft_cmd_lstclear(t_cmd_lst **lst, void (*del)(void*));
void		ft_cmd_lstdelone(t_cmd_lst *lst, void (*del)(void*));
void		ft_cmd_lstiter(t_cmd_lst *lst, void (*f)(void *));
t_cmd_lst	*ft_cmd_lstlast(t_cmd_lst *lst);
t_cmd_lst	*ft_cmd_lstnew(void *str, void *flag, int index);
int			ft_cmd_lstsize(t_cmd_lst *lst);

void		ft_env_to_lst(char **env, t_sh *sh);
char		*ft_is_var(char *str, t_sh *sh);

void		dbg(t_sh *t);

#endif

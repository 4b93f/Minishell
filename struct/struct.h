/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:15:25 by chly-huc          #+#    #+#             */
/*   Updated: 2021/08/09 20:40:48 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H
#include "../env/env.h"
#include "../cmd/cmd.h"
#include "../lib/libft/libft.h"
#include "../lib/get_next_line/get_next_line.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "errno.h"

#define CMD_NOT_FOND -1
#define PERM_DENIED 13
#define IS_DIRECTORY 21
#define PIPE 666 

enum e_boolean
{
	FALSE = 0,
	TRUE
};

typedef struct	s_sh
{
	char *input_str;
	char **all_path;
	int flag_n;
	char *free_ptr;
	int fd_in;
	int fd_out;
	int fd_backup[2];
	int **fd_pipe;
	pid_t child_pid;
	int piped[2];

	t_lst_cmd *lst_cmd;
	t_lst_cmd *ptr_cmd;
	
	t_lst_env *lst_env;
	t_lst_env *ptr_env;
}				t_sh;

void str_tolst(char *str, t_sh *sh);
void	ft_print_lst(t_lst_cmd *lst);
t_sh	*ft_malloc_sh(void);
void	env_tolst(char **env, t_sh *sh);
char *env_lstcontent(t_sh *sh, char *str);
char *dollarz(t_sh *sh, char *str);
void env_setup(t_sh *sh, char **env);
void is_quote_open(char *str, int *squote, int *dquote, int i);
t_lst_env	*env_lstfinder(t_lst_env *lst, char *var);
char	*get_actual_path(void);
void ft_echo(t_sh *sh);
char *ft_remove_char(char *str, int c);
void start(t_sh *sh);
void	print_env(t_sh *sh);
void ft_pwd(t_sh *sh);
void sh_free(t_sh *sh);
void ft_exit(t_sh *sh);
void ft_export(t_sh *sh);
void ft_print_tab(char **str);
int env_lstdupe(t_sh *sh, char *var, char *value);
void	ft_print_env(t_lst_env *lst);
void 	env_lstedit(t_sh *sh, char *var, char *value);
char	**lst_to_tab(t_lst_env *lst);
void ft_unset(t_sh *sh);
void env_lstdel(t_sh *sh, t_lst_env *delcontent);
void ft_cd(t_sh *sh);
void exec_cmd(t_sh *sh);
void	get_all_path(t_sh *sh);
char	*ft_search_path(t_sh *sh, char *str);
void exit_code(t_sh *sh, int nbr);
void pipe_n_red(t_sh *sh);
int str_sep(char *str);
int error(char *str, int error);
char **lstenv_to_tab(t_sh *sh);


#endif

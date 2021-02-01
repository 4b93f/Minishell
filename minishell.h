/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:05:21 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/01 03:29:56 by jsilance         ###   ########.fr       */
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
# include "get_next_line/get_next_line.h"
# include <math.h>
# include <stdlib.h>

enum		e_error
{
	MALLOC_ERROR,
	EXIT_TO_MANY_ARG,
	EXIT_ILLEGAL,
	EXIT_NUM
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

	t_list		*str;
	
	int			pid;
	
	void		*next;
}				t_cmd_lst;


typedef struct	s_sh
{
	char **all_path; //--> liste chainee

	char		*input_str;

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
void		free_tab(char **tab);
void		print_tab(char **str);
void		print_env(t_env_lst *lst, int fd);
void		get_pwd(t_sh *sh);
void		create_env(t_sh *sh, char *new_env);
void		get_all_path(t_sh *sh);
void		exec_cmd(t_cmd_lst *cmd, t_sh *sh);
void		ft_export(t_cmd_lst *cmd, t_sh *sh);
void		cd_info(t_sh *sh, int num, char *path);
void		ft_unset(t_cmd_lst *cmd, t_sh *sh);
void		ft_pwd(t_cmd_lst *cmd);
int			ft_isspace(int c);

void		strtolst(t_sh *t);
int			parser(t_sh *t);
t_env_lst	*env_lst_finder(t_env_lst *lst, char *var);
void		sh_free(t_sh *sh);
void		ft_error(int ret, t_sh *sh, int ext);
char		*ft_search_path(t_sh *sh, t_cmd_lst *cmd);
void		ft_free_sh(t_sh *sh);
char		*rm_guim(char *ptr);
void		ft_exit(t_cmd_lst *cmd, t_sh *sh);

int			executor(t_sh *sh);

void			ft_env_lstadd_back(t_env_lst **alst, t_env_lst *new);
void			ft_env_lstadd_front(t_env_lst **alst, t_env_lst *new);
void			ft_env_lstclear(t_env_lst **lst, void (*del)(void*));
void			ft_env_lstdelone(t_env_lst *lst, void (*del)(void*));
void			ft_env_lstiter(t_env_lst *lst, void (*f)(void *));
t_env_lst		*ft_env_lstlast(t_env_lst *lst);
t_env_lst		*ft_env_lstnew(void *var, void *content);
int				ft_env_lstsize(t_env_lst *lst);

void			ft_cmd_lstadd_back(t_cmd_lst **alst, t_cmd_lst *new);
void			ft_cmd_lstadd_front(t_cmd_lst **alst, t_cmd_lst *new);
void			ft_cmd_lstclear(t_cmd_lst **lst, void (*del)(void*));
void			ft_cmd_lstdelone(t_cmd_lst *lst, void (*del)(void*));
void			ft_cmd_lstiter(t_cmd_lst *lst, void (*f)(void *));
t_cmd_lst		*ft_cmd_lstlast(t_cmd_lst *lst);
t_cmd_lst		*ft_cmd_lstnew(void *str, void *flag, int index);
int				ft_cmd_lstsize(t_cmd_lst *lst);

void			ft_env_to_lst(char **env, t_sh *sh);
char			*ft_is_var(char *str, t_sh *sh);

void			dbg(t_sh *t);

#endif

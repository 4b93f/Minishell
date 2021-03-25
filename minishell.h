/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:05:21 by chly-huc          #+#    #+#             */
/*   Updated: 2021/03/25 18:19:44 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H

# define MAIN_H

# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "structs.h"
# include "env_cl/ft_env_cl.h"
# include "cmd_cl/ft_cmd_cl.h"
# include "executor/executor.h"
# include <stdio.h>
# include "get_next_line/get_next_line_bonus.h"
# include <math.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>

#define PERM_DENIED 13
#define	UP 1

t_sh		ft_create_sh(void);
t_sh		*ft_malloc_sh(void);
void		ft_free_sh(t_sh *sh);


void		sh_free(t_sh *sh);
int			ft_print_error(int ret, char *str);
void		ft_error(int ret, t_sh *sh, int ext);
void		ft_error_two(char *str, t_sh *sh, int ext);


void		strtolst(t_sh *t);


char		*quoting(char *str);
void		str_store(t_sh *t, int j, int i, int sep);
int			is_double_char(t_sh *t, int i);


void		parser(t_sh *t);

int			sep_checker(char *str);
int			lex_to_cmdstr(t_sh *sh);
int			cmd_checker(char *str);
int			cmd_flag_check(char *str);
void		backsl(t_list *ptr);

int			set_pipe_red(t_sh *sh);


void		dbg(t_sh *t);
int			parse_input(t_sh *sh);


char		*get_actual_path(void);
void		ft_retval_init(t_sh *sh);


char		*ft_search_path(t_sh *sh, t_cmd_lst *cmd);
void		get_all_path(t_sh *sh);


int			tablen(char **tab);
void		*free_tab(char **tab);
char		*ft_strjoinfree(const char *s1, const char *s2);
t_env_lst	*env_lst_finder(t_env_lst *lst, char *var);
void		print_env(t_env_lst *lst, int fd, t_sh *sh);


void		print_tab(char **str);
int			ft_isspace(int c);
int			ft_stat(char *filename, t_sh *sh);
int			ft_error_stat(int ret, t_sh *sh);
void		ft_env_to_lst(char **env, t_sh *sh);

#endif

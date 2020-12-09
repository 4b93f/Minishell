/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:05:21 by chly-huc          #+#    #+#             */
/*   Updated: 2020/12/08 17:54:51 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include <sys/types.h>

typedef struct	s_sh
{
	char	**env;
	char **all_path;
	char *built_in;
	char *old_pwd;
	char *actual_pwd;
}				t_sh;


t_sh		*ft_malloc_sh();
int			tablen(char **tab);
int			sort_export(t_sh *sh, int i, int j, int len);
char		**ft_realloc(char **str, char *line);
char		**tabcpy(char **tab);
char		*ft_strjoinfree(const char *s1, const char *s2);
char		**delete_env(t_sh *sh, char *delete_env, int len);
void		free_tab(char **tab);
void		print_tab(char **str);
void		get_pwd(t_sh *sh);
void		create_env(t_sh *sh, char *new_env);
void		get_all_path(t_sh *sh);
void		ft_cd(t_sh *sh);
void		ft_echo(t_sh *sh);
void		ft_ls();
void		ft_export(t_sh *sh);
void		cd_info(t_sh *sh, int num, char *path);
void		ft_exit(t_sh *sh);
void		ft_unset(t_sh *sh);
char *get_actual_path(void);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:12:12 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/08 21:45:12 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H

# define EXECUTOR_H

# include "../minishell.h"

void		ft_cd(t_cmd_lst *cmd, t_sh *sh);

void		ft_echo(t_cmd_lst *cmd, t_sh *sh);

void		exec_cmd(t_cmd_lst *cmd, t_sh *sh);

char		*ft_is_var(char *str, t_sh *sh);
char		*rm_guim(char *ptr);
void		ft_portal(t_sh *sh, int ret, int pid, int fd[2]);
char		**lst_db_tab(t_cmd_lst *cmd);

char		*ft_str_isalnum(char *str);
void		ft_set_free_env(t_sh *sh, void *var, void *content);
char		**ft_lst_to_tab(t_env_lst *lst);
char		**envlst_to_tab(t_env_lst *lst);
void		print_declare(t_sh *sh, t_cmd_lst *cmd, char **tab, int i);

char		*fulltrim(char *s1, int c);
char		*ft_backslash(char *s1);

int			executor(t_sh *sh);

void		ft_exit(t_cmd_lst *cmd, t_sh *sh);

void		ft_export(t_cmd_lst *cmd, t_sh *sh);

void		ft_pwd(t_cmd_lst *cmd, t_sh *sh);

void		ft_unset(t_cmd_lst *cmd, t_sh *sh);

#endif
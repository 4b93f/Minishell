/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:04:42 by chly-huc          #+#    #+#             */
/*   Updated: 2020/12/09 14:49:59 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_actual_path(void)
{
	char *buf;
	char *str;
	buf = NULL;
    int size = 40000;
	str = getcwd(buf, size);
	return(str);
}

void get_pwd(t_sh *sh)
{
	int i;

	i = -1;
	while(sh->env[++i])
	{
		if (sh->old_pwd && !ft_strncmp(sh->env[i], "OLDPWD", ft_strlen("OLDPWD")))
		{
			free(sh->env[i]);
			sh->env[i] = ft_strjoin("OLDPWD=", sh->old_pwd);
		}
	}
	i = -1;
	while(sh->env[++i])
	{
		if (sh->actual_pwd && !ft_strncmp(sh->env[i], "PWD", ft_strlen("PWD")))
		{
			free(sh->env[i]);
			sh->env[i] = ft_strjoin("PWD=", sh->actual_pwd);
		}
	}
}

void ft_scan(t_sh *sh)
{
	if (!strcmp(sh->built_in, "pwd"))
		ft_pwd();
	if (!strncmp(sh->built_in, "cd", 2))
		ft_cd(sh);
	if (!strcmp(sh->built_in, "ls"))
		ft_ls();
	if (!strncmp(sh->built_in, "echo", 4))
		ft_echo(sh);
	if (!strncmp(sh->built_in, "export", 6))
		ft_export(sh);
	if (!strncmp(sh->built_in, "unset", 5))
		ft_unset(sh);
	if (!strcmp(sh->built_in, "exit"))
		ft_exit(sh);
	if (!strcmp(sh->built_in, "env"))
		print_tab(sh->env);
	if (!strcmp(sh->built_in, "path"))
		print_tab(sh->all_path);
}

int main(int argc, char **argv, char **env)
{
	t_sh *sh;
	sh = ft_malloc_sh();
	sh->env = tabcpy(env);
	get_all_path(sh);
	while(1)
	{
		write(0, "My Minishell ~> ", 16);
		get_next_line(0, &sh->built_in);
		ft_scan(sh);
		free(sh->built_in);
		get_pwd(sh);
	}
	return (1);
}

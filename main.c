/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:04:42 by chly-huc          #+#    #+#             */
/*   Updated: 2020/12/09 19:35:22 by chly-huc         ###   ########.fr       */
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
	sh->built_in = ft_strtrim(sh->built_in, " ");
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

int check_syntax(t_sh *sh)
{
	int i;
	int error;

	i = -1;
	error = 0;
	while (sh->built_in[++i])
	{
		if (sh->built_in[i] == '\\' && sh->built_in[i + 1] == ';')
			error++;
	}
	return (error == 0 ? 1 : 0);
}

int main(int argc, char **argv, char **env)
{
	t_sh *sh;
	sh = ft_malloc_sh();
	sh->env = tabcpy(env);
	get_all_path(sh);
	while(1)
	{
		int i = -1;
		write(0, "My Minishell ~> ", 16);
		get_next_line(0, &sh->built_in);
		if (check_syntax(sh))
			sh->tmp = ft_split(sh->built_in, ';');
		print_tab(sh->tmp);
		while (sh->tmp[++i])
		{
			free(sh->built_in);
			sh->built_in = ft_strdup(sh->tmp[i]);
			free(sh->tmp[i]);
			ft_scan(sh);
			get_pwd(sh);
		}
		free(sh->tmp);
		free(sh->built_in);
	}
	return (1);
}

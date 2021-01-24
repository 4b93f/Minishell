/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:04:42 by chly-huc          #+#    #+#             */
/*   Updated: 2021/01/23 23:23:26 by jsilance         ###   ########.fr       */
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
	sh->input_str = ft_strtrim(sh->input_str, " ");
	if (!strcmp(sh->input_str, "pwd"))
		ft_pwd();
	if (!strncmp(sh->input_str, "cd", 2))
		ft_cd(sh);
	if (!strcmp(sh->input_str, "ls"))
		ft_ls();
	if (!strncmp(sh->input_str, "echo", 4))
		ft_echo(sh);
	if (!strncmp(sh->input_str, "export", 6))
		ft_export(sh);
	if (!strncmp(sh->input_str, "unset", 5))
		ft_unset(sh);
	if (!strcmp(sh->input_str, "exit"))
		ft_exit(sh);
	if (!strcmp(sh->input_str, "env"))
		print_tab(sh->env);
	if (!strcmp(sh->input_str, "path"))
		print_tab(sh->all_path);
}

int check_syntax(t_sh *sh)
{
	int i;
	int error;

	i = -1;
	error = 0;
	while (sh->input_str[++i])
	{
		if (sh->input_str[i] == '\\' && sh->input_str[i + 1] == ';')
			error++;
	}
	return (error == 0 ? 1 : 0);
}

int main(int argc, char **argv, char **env)
{
	t_sh	sh;
	// char	**tmp_env;

	ft_env_to_lst(env, &sh);
	
	get_all_path(&sh);
	while(1)
	{
		int i = -1;
		write(0, "My Minishell ~> ", 16);
		get_next_line(0, sh.input_str);
		if (check_syntax(&sh))
			sh.tmp = ft_split(sh.input_str, ';');
		print_tab(sh.tmp);
		while (sh.tmp[++i])
		{
			free(sh.input_str);
			sh.input_str = ft_strdup(sh.tmp[i]);
			free(sh.tmp[i]);
			ft_scan(&sh);
			get_pwd(&sh);
		}
		free(sh.tmp);
		free(sh.input_str);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 13:33:07 by chly-huc          #+#    #+#             */
/*   Updated: 2020/12/09 18:18:25 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd()
{
    char *buf;
	int size;
	
	size = 40000;
	buf = NULL;
	
    buf = getcwd(buf, size);
	printf("%s\n", buf);
	free(buf);
}

void ft_cd(t_sh *sh)
{
	struct stat buffer;
	char *path;
	int i;
	
	i = 0;
	path = NULL;
	free(sh->old_pwd);
	sh->old_pwd = get_actual_path(); 
	if (!strcmp("cd /", sh->built_in))
		chdir("/");
	if (!strcmp("cd ~", sh->built_in) || !strcmp("cd", sh->built_in))
	{
		while(strncmp(sh->env[i], "HOME=", ft_strlen("HOME=")))
			i++;
		chdir(sh->env[i] + ft_strlen("HOME="));
	}
	i = stat("/Users/chly-huc/Desktop/minish", &buffer);
	path = get_actual_path();
	path = ft_strjoinfree(path, "/");
	path = ft_strjoinfree(path, sh->built_in + ft_strlen("cd "));
	if (i == -1)
		return ;
	else
	{
		if (S_ISDIR(buffer.st_mode))
			chdir(path);
	}
	free(sh->actual_pwd);
	sh->actual_pwd = get_actual_path();
	free(path);
}

void ft_echo(t_sh *sh)
{
	char *str;

	int i;

	i = 0;
	if (!strcmp(sh->built_in, "echo"))
		return ;
	if (!strncmp(sh->built_in, "echo -n", ft_strlen("echo -n")))
		write(1, sh->built_in + ft_strlen("echo -n") + 1, ft_strlen(sh->built_in + ft_strlen("echo -n") + 1));
	else
		printf("%s\n", sh->built_in + ft_strlen("echo") + 1);
	
}

void ft_ls()
{
	pid_t child_pid;
	pid_t dad_pid;
	char **tmp;
	
	child_pid = fork();
	if (!(tmp = malloc(sizeof(char*) * 2)))
		return ;
	tmp[0] = "ls";
	tmp[1] = 0;
	if (child_pid == 0)
		execve("/bin/ls", tmp, NULL);
	else
		dad_pid = wait(&child_pid);
	free(tmp);
}

int  sort_export(t_sh *sh, int i, int j, int len)
{
	char *tmp;
	char **ok;
	int modif;
	
	modif = 0;
	i = -1;
	ok = tabcpy(sh->env);
	while(modif == 0)
	{
		i = 0;
		modif = 1;
		while (i < len - 1)
		{
			if (ok[i] && strcmp(ok[i], ok[i + 1]) > 0)
			{
				tmp = ok[i];
				ok[i] = ok[i + 1];
				ok[i + 1] = tmp;
				modif = 0;
			}
			i++;
		}
		len--;
	}
	print_tab(ok);
	free_tab(ok);
	return (0);
}


void ft_export(t_sh *sh)
{
	int i;
	int j;
	int k;
	char **tab;
	
	i = 0;
	j = 0;
	k = 0;
	tab = NULL;
	if (!(tab = ft_split(sh->built_in, ' ')))
		return;
	if (!strcmp(sh->built_in, "export"))
		sort_export(sh, 0, 0, tablen(sh->env));
	while (tab[++k])
	{
		if (ft_strchr(tab[k], '='))
		{
			j = 0;
			i = 0;
			while (tab[k][i] && tab[k][i] != '=')
				i++;
			while (sh->env[j] && tab[k] && ft_strncmp(sh->env[j], tab[k], i))
				j++;
			if (!sh->env[j])
				create_env(sh, tab[k]);
			else
			{
				if (ft_strchr(tab[k], '='))
				{
					free(sh->env[j]);
					sh->env[j] = ft_strdup(tab[k]);
				}
			}
		}
	}
	free_tab(tab);
}

void ft_unset(t_sh *sh)
{
	int i;
	int j;
	int len;
	char **tab;
	
	i = 0;
	j = 0;
	if (!(tab = ft_split(sh->built_in, ' ')))
		return ;
	while (tab[++i])
	{
		j = 0;
		while (sh->env[j] && ft_strncmp(sh->env[j], tab[i], ft_strlen(tab[i])))
			j++;
		if (!sh->env[j])
		{
			free_tab(tab);
			return ;
		}
		else
		{
			len = tablen(sh->env);
			sh->env = delete_env(sh, tab[i], len);
		}
	}
	free_tab(tab);
}

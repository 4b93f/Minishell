/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:56:08 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/29 18:12:09 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

char **lstenv_to_tab(t_sh *sh)
{
	int len;
	char **dup;
	char *tmp;

	sh->ptr_env = sh->lst_env;
	len = env_lstsize(sh->ptr_env);
	sh->ptr_env = sh->lst_env;
	dup = malloc(sizeof(char *) * (len + 1));
	len = 0;
	while (sh->ptr_env)
	{
		tmp = ft_strjoin(sh->ptr_env->var, "=");
		if (!tmp)
			return (NULL);
		dup[len] = ft_strjoin(tmp, sh->ptr_env->content);
		if (!dup[len])
			return (NULL);
		free(tmp);
		len++;
		sh->ptr_env = sh->ptr_env->next;
	}
	dup[len] = NULL;
	return (dup);
}

char	**lstcmd_to_tab(t_sh *sh)
{
	char	**ptr;
	sh->ptr_cmd = sh->lst_cmd;
	int		size;

	ptr = NULL;
	size = cmd_lstsize(sh->ptr_cmd);
	sh->ptr_cmd = sh->lst_cmd;
	ptr = ft_calloc(sizeof(char *), size + 2);
	if (!ptr)
		return (NULL);
	size = -1;
	ptr[++size] = ft_strdup(sh->ptr_cmd->cmd);
	if (!ptr)
		return (NULL);
	while (sh->ptr_cmd)
	{
		ptr[++size] = ft_strdup(sh->ptr_cmd->cmd);
		if (!ptr)
			return (NULL);
		sh->ptr_cmd = sh->ptr_cmd->next;
	}
	return (ptr);
}


void exec_cmd(t_sh *sh)
{
	errno = 0;
	char *file;
	char **envp;
	char **argp;

	sh->ptr_cmd = sh->lst_cmd;
	file = ft_strjoin(ft_search_path(sh, sh->ptr_cmd->cmd), sh->ptr_cmd->cmd);
	//printf("file =[%s]\n", file);
	envp = lstenv_to_tab(sh);
	argp = lstcmd_to_tab(sh);
	sh->child_pid = fork();
	if (!sh->child_pid)
	{
		//print_tab(argp);
		//printf("!\n");
		//print_tab(envp);
		errno = execve(file, argp, envp);
		//printf("?\n");
		if (errno == -1)
			printf("COMMAND NOT FOUND\n");
		exit(0);
	}
	wait(0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:56:08 by chly-huc          #+#    #+#             */
/*   Updated: 2021/08/10 06:30:30 by shyrno           ###   ########.fr       */
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

char	**lstcmd_to_tab(t_lst_cmd *lst)
{
	char	**ptr;
	t_lst_cmd	*ptr_lst;
	int		size;

	ptr = NULL;
	ptr_lst = lst;
	while (ptr_lst)
	{
		if (str_sep(lst->cmd))
			break;
		ptr_lst = ptr_lst->next;
		size++;
	}
	ptr = ft_calloc(sizeof(char *), size + 2);
	if (!ptr)
		return (NULL);
	size = 0;
	if (!ptr)
		return (NULL);
	while (lst && !str_sep(lst->cmd))
	{
		if (!ptr)
			return (NULL);
		ptr[size] = ft_strdup(lst->cmd);
		lst = lst->next;
		size++;
	}
	ptr[size] = NULL;
	return (ptr);
}


void exec_cmd(t_sh *sh)
{
	errno = 0;
	char *file;
	char **envp;
	char **argp;
	pid_t pid;
	pid_t exit_pid;

	//printf("In exec_cmd with cmd = %s\n", sh->ptr_cmd->cmd);
	file = ft_strjoin(ft_search_path(sh, sh->ptr_cmd->cmd), sh->ptr_cmd->cmd);
	envp = lstenv_to_tab(sh);
	argp = lstcmd_to_tab(sh->ptr_cmd);
	pid = fork();
	if (pid == 0)
	{
		errno = execve(file, argp, envp);
		error(argp[0]);
		exit(0);
	}
	else if (pid == -1)
		printf("Error\n");
	else
	{
		//close(sh->fd_in);
		//close(sh->fd_out);
		waitpid(pid, &exit_pid, 0);
		//printf("!\n");
	}
	//printf("Out exec_cmd with cmd = %s\n", sh->ptr_cmd->cmd);
}
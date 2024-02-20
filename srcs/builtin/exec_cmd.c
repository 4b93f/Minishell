/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:56:08 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/12 18:07:41 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

static char	**lstenv_to_tab(t_sh *sh)
{
	int		len;
	char	**dup;
	char	*tmp;

	sh->ptr_env = sh->lst_env;
	len = env_lstsize(sh->ptr_env);
	sh->ptr_env = sh->lst_env;
	dup = malloc(sizeof(char *) * (len + 1));
	if (!dup)
		return (NULL);
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

static char	**lstcmd_to_tab(t_lst_cmd *lst)
{
	char		**ptr;
	t_lst_cmd	*ptr_lst;
	int			size;

	size = 0;
	ptr = NULL;
	ptr_lst = lst;
	while (ptr_lst)
	{
		if (str_sep(lst->cmd))
			break ;
		ptr_lst = ptr_lst->next;
		size++;
	}
	ptr = malloc_tab(size, lst);
	return (ptr);
}

static void	forked(t_sh *sh, char *file, char **envp, char **argp)
{
	signal(SIGQUIT, SIG_DFL);
	if (sh->fd_out != -1)
	{
		if (execve(file, argp, envp) < 0)
		{
			ft_putstr_fd("My minishell: ", 2);
			ft_putendl_fd(strerror(errno), 2);
		}
		free_tab(envp);
		free_tab(argp);
		free(file);
		if (errno == EAGAIN)
			exit(126);
		exit(127);
	}
	else
		exit(1);
}

void	dad_work(t_sh *sh, int pid)
{
	if (pid < 0)
	{
		ft_putstr_fd("My Minishell: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else
		waitpid(pid, &sh->exit_code, 0);
	if (WIFEXITED(pid))
		sh->exit_code = WEXITSTATUS(pid);
	else
		sh->exit_code = sh->exit_code / 256;
}

void	exec_cmd(t_sh *sh, char *file, char **envp, char **argp)
{
	pid_t	pid;

	errno = 0;
	if (ft_strlen(sh->ptr_cmd->cmd) == 0)
		file = ft_strjoin(ft_search_path(sh, sh->ptr_cmd->cmd), " ");
	else
		file = ft_strjoin(ft_search_path(sh, sh->ptr_cmd->cmd),
				sh->ptr_cmd->cmd);
	envp = lstenv_to_tab(sh);
	argp = lstcmd_to_tab(sh->ptr_cmd);
	pid = fork();
	if (pid == 0)
		forked(sh, file, envp, argp);
	else
		dad_work(sh, pid);
	free_tab(envp);
	free_tab(argp);
	free(file);
}

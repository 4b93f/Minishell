/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:16:59 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/16 22:18:30 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include "executor.h"

static void	ft_not_found(t_cmd_lst *cmd, t_sh *sh, int pid, int fd[2])
{
	int	ret;

	ret = 0;
	if (ft_strnstr(cmd->cmd_str, "./", ft_strlen(cmd->cmd_str))
		|| ft_strchr(cmd->cmd_str, '/'))
		ret = ft_stat(cmd->cmd_str, sh);
	else
	{
		ft_putstr_fd("minishell: ", sh->cmd->fd_pipe_out);
		ft_putstr_fd(cmd->cmd_str, cmd->fd_pipe_out);
		ft_putstr_fd(": command not found\n", cmd->fd_pipe_out);
		ft_portal(sh, 127, pid, fd);
	}
	if (ret == 0 || ret == 1)
		ft_portal(sh, 126, pid, fd);
}

void	exec_cmd(t_cmd_lst *cmd, t_sh *sh)
{
	char	**tmp;
	char	**tmpenv;
	char	*ptr;
	int		portal[2];

	errno = 0;
	ptr = ft_strjoin(ft_search_path(sh, cmd), cmd->cmd_str);
	if (!ptr)
		return ;
	tmp = lst_db_tab(cmd);
	tmpenv = envlst_to_tab(sh->env_lst);
	if (pipe(portal) < 0)
		ft_error(PIPE_ERROR, sh, 0);
	cmd->child_pid = fork();
	if (!cmd->child_pid)
	{
		errno = execve(ptr, tmp, tmpenv);
		if (errno == -1)
			ft_not_found(cmd, sh, cmd->child_pid, portal);
		else
			ft_portal(sh, errno, cmd->child_pid, portal);
		exit(0);
	}
	if (cmd->pipe_in != S_LEFT_RED)
	{
		ft_portal(sh, errno, cmd->child_pid, portal);
		wait(0);
	}
	if (errno == 2)
		strerror(errno);
	free(ptr);
	free_tab(tmp);
	free_tab(tmpenv);
}

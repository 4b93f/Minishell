/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:16:59 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/17 16:49:01 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include "executor.h"

static void	ft_not_found(t_cmd_lst *cmd, t_sh *sh, int pid, int fd[2])
{
	int ret;
	ret = 0;
	if (ft_strnstr(cmd->cmd_str, "./", ft_strlen(cmd->cmd_str)) || ft_strchr(cmd->cmd_str, '/'))
	{
		ret = ft_stat(cmd->cmd_str, sh);
	}
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
	pid_t	child_pid;
	char	**tmp;
	char	**tmpenv;
	char	*ptr;
	char	*sf;
	int		portal[2];
	int		ret;
	int errno;

	errno = 0;
	sf = ft_search_path(sh, cmd);
	ptr = ft_strjoin(sf, cmd->cmd_str);
	if (!ptr)
		return;
	tmp = lst_db_tab(cmd);
	tmpenv = envlst_to_tab(sh->env_lst);
	if (pipe(portal) < 0)
		ft_error(PIPE_ERROR, sh, 0);
	//printf("!\n");
	child_pid = fork();
	if (!child_pid)
	{
		if ((errno = execve(ptr, tmp, tmpenv)) == -1)
			ft_not_found(cmd, sh, child_pid, portal);
		else
			ft_portal(sh, errno, child_pid, portal);
		exit(0);
	}
	wait(0);
	ft_portal(sh, errno, child_pid, portal);
	//printf("errno==%d\n", errno);
	if (errno == 2)
		strerror(errno);
	free(ptr);
	free_tab(tmp);
	free_tab(tmpenv);
}

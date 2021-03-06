/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 01:19:10 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/16 22:34:20 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include "executor.h"

static void	commander_exec(t_cmd_lst *cmd, t_sh *sh)
{
	if (cmd->str)
		ft_set_free_env(sh, "_", ft_strdup(ft_lstlast(cmd->str)->content));
	else
		ft_set_free_env(sh, "_", ft_strjoin(ft_search_path(sh, cmd), cmd->cmd_str));
	if (cmd->cmd_index == -1)
		exec_cmd(cmd, sh);
	else if (cmd->cmd_index == 0)
		ft_exit(cmd, sh);
	else if (cmd->cmd_index == 1)
		ft_echo(cmd, sh);
	else if (cmd->cmd_index == 2)
		ft_cd(cmd, sh);
	else if (cmd->cmd_index == 3)
		ft_pwd(cmd, sh);
	else if (cmd->cmd_index == 4)
		ft_export(cmd, sh);
	else if (cmd->cmd_index == 5)
		ft_unset(cmd, sh);
	else if (cmd->cmd_index == 6)
		print_env(sh->env_lst, cmd->fd_pipe_out, sh);
}

static void	fork_piper(t_cmd_lst *ptr_cmd, t_sh *sh)
{
	int			pid;
	t_cmd_lst	*ccmd;
	int			fd_backup[2];

	fd_backup[0] = dup(0);
	fd_backup[1] = dup(1);
	ccmd = ptr_cmd->next;
	dup2(ptr_cmd->fd_pipe_out, 1);
	dup2(ccmd->fd_pipe_in, 0);
	pid = fork();
	if (pid)
	{
		close(ptr_cmd->fd_pipe_out);
		ptr_cmd = ptr_cmd->next;
		ptr_cmd->pid = pid;
		dup2(fd_backup[1], 1);
		dup2(ptr_cmd->fd_pipe_in, 0);
	}
	else
	{
		close(ccmd->fd_pipe_in);
		ptr_cmd->pid = pid;
	}
	wait(0);
	commander_exec(ptr_cmd, sh);
	//printf("!\n");
	if (!pid)
	{
		if (ptr_cmd->fd_pipe_out > 2)
			close(ptr_cmd->fd_pipe_out);
		exit(0);
	}
	wait(0);
	close(ptr_cmd->fd_pipe_in);
	dup2(fd_backup[0], 0);
	kill(pid, SIGQUIT);
}

int	executor(t_sh *sh)
{
	t_cmd_lst	*ptr_cmd;
	t_cmd_lst	*ptr_cmd_next;
	char		*buf;
	int			ret;
	char		*str;

	buf = NULL;
	ptr_cmd = sh->cmd;
	while (ptr_cmd)
	{
		// if (!ptr_cmd->red_file)
		// {
		// 	ft_putstr_fd("minishell: ", ptr_cmd->fd_pipe_out);
		// 	ft_print_error(SYNTAX_ERROR, "newline");
		// 	ft_set_free_env(sh, "?", ft_itoa(2));
		// 	return (-1);
		// }
		ptr_cmd_next = NULL;
		if (ptr_cmd->next)
			ptr_cmd_next = ptr_cmd->next;
		if (ptr_cmd->pipe_out == S_RIGHT_RED)
		{
			ptr_cmd->fd_pipe_out = open(ptr_cmd->red_file->content,
					O_CREAT | O_WRONLY | O_TRUNC, 0777);
			if (ptr_cmd->fd_pipe_out < 0)
				ft_error(0, sh, 1);
		}
		if (ptr_cmd->pipe_out == D_RIGHT_RED)
		{
			ptr_cmd->fd_pipe_out = open(ptr_cmd->red_file->content,
					O_CREAT | O_APPEND | O_WRONLY, 0777);
			if (ptr_cmd->fd_pipe_out < 0)
				ft_error(0, sh, 1);
		}
		if (ptr_cmd->pipe_in == S_LEFT_RED)
		{
			if (ptr_cmd->red_file)
			{	
				ptr_cmd->fd_pipe_in = open(ptr_cmd->red_file->content,
						O_APPEND | O_RDONLY, 0777);
				ret = 1;
			}
			else
			{
				printf("minishell: No such file or directory.\n");
				return (-1);
			}
			while (ret)
			{
				ret = get_next_line(ptr_cmd->fd_pipe_in, &str);
				ft_putstr_fd(str, 0);
				free(str);
			}
			if (ptr_cmd->fd_pipe_in < 0)
			{
				ft_putstr_fd("minishell: ", ptr_cmd->fd_pipe_out);
				ft_print_error(NO_SUCH_FILE, (char *)ptr_cmd->red_file->content);
				return (-1);
			}
		}
		if (ptr_cmd->pipe_out == PIPE && ptr_cmd->next)
		{
			if (ptr_cmd_next->cmd_index == 1 && ptr_cmd->cmd_index == -1)
			{
				ptr_cmd->fd_pipe_out = 1;
				fork_piper(ptr_cmd, sh);
				ptr_cmd = ptr_cmd->next;
			}
			else
			{
				fork_piper(ptr_cmd, sh);
				if (ptr_cmd->fd_pipe_out > S_RIGHT_RED)
					close(ptr_cmd->fd_pipe_out);
				if (ptr_cmd->fd_pipe_out && ptr_cmd->next)
					ptr_cmd = ptr_cmd->next;
			}
		}
		else
		{
			commander_exec(ptr_cmd, sh);
			if (ptr_cmd->fd_pipe_out > 2)
				close(ptr_cmd->fd_pipe_out);
		}
		if (ptr_cmd->pipe_in == S_LEFT_RED)
		{
			kill(ptr_cmd->child_pid, 1);
			write(0, "\n", 1);	
		}
		ptr_cmd = ptr_cmd->next;
	}
	return (0);
}

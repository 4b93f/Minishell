/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 01:19:10 by jsilance          #+#    #+#             */
/*   Updated: 2021/01/26 01:22:12 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static void	cmd_pwd(t_cmd_lst *cmd_ptr)
{
	char	*ptr;

	ptr = pather();
	ft_putstr_fd(ptr, cmd_ptr->fd_pipe_out);
	if (cmd_ptr->fd_pipe_out == 1)
		write(1, "\n", 1);
	free(ptr);
}

/*
**	/!\ gerer si plus que flag et arg
**	/!\ gerer erreur de guillemet + trim
*/



static void	cmd_echo(t_cmd_lst *cmd_ptr)
{
	t_list	*ptr_lst;

	ptr_lst = cmd_ptr->str;
	while (ptr_lst)
	{
		ft_putstr_fd(ptr_lst->content, cmd_ptr->fd_pipe_out);
		ptr_lst = ptr_lst->next;
		if (ptr_lst)
			write(cmd_ptr->fd_pipe_out, " ", 1);
		else if (!(cmd_ptr->flags && !ft_strcmp("-n", cmd_ptr->flags)))
			write(cmd_ptr->fd_pipe_out, "\n", 1);
	}
}




static void	cmd_help(t_cmd_lst *cmd_ptr)
{
	ft_putstr_fd("\nCommands list:\n\nexit\necho [-n] [arg]\ncd [arg]\npwd\nexport [arg]\nunset [arg]\nenv\nhelp\n\n", cmd_ptr->fd_pipe_out);
}





static void	cmd_cd(t_cmd_lst *cmd_ptr)
{
	if (chdir(cmd_ptr->str->content))
		ft_error(2, 0);
}





static void	commander_exec(t_cmd_lst *ptr_cmd, t_sh *sh)
{
	if (ptr_cmd->cmd_index == -1)
		ft_error(1, 0); //execve
	else if (ptr_cmd->cmd_index == 0)
		exiturn(sh, 1);
	else if (ptr_cmd->cmd_index == 1)
		cmd_echo(ptr_cmd);
	else if (ptr_cmd->cmd_index == 2)
		cmd_cd(ptr_cmd);
	else if (ptr_cmd->cmd_index == 3)
		cmd_pwd(ptr_cmd);
	else if (ptr_cmd->cmd_index == 7)
		cmd_help(ptr_cmd);
}

static void	fork_piper(t_cmd_lst *ptr_cmd, t_sh *sh)
{
	int	pid;

	pid = fork();
	if (pid)
	{
		ptr_cmd = ptr_cmd->next;
		ptr_cmd->pid = pid;
	}
	else
		ptr_cmd->pid = pid;
	wait(0);
	commander_exec(ptr_cmd, sh);
	if (!pid)
		exit(0);
}

int	executor(t_sh *sh)
{
	t_cmd_lst	*ptr_cmd;

	ptr_cmd = sh->cmd;
		// dbg(t);
	while (ptr_cmd)
	{
		if (ptr_cmd->pipe_out)
		{
			fork_piper(ptr_cmd, sh);
			if (ptr_cmd->fd_pipe_out)
				ptr_cmd = ptr_cmd->next;
		}
		else
			commander_exec(ptr_cmd, sh);
		ptr_cmd = ptr_cmd->next;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 01:19:10 by jsilance          #+#    #+#             */
/*   Updated: 2021/01/30 01:34:25 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	/!\ gerer si plus que flag et arg.
**	/!\ gerer erreur de guillemet + trim.
*/

static void	ft_echo(t_cmd_lst *cmd, t_sh *sh)
{
	t_list	*ptr_lst;

	ptr_lst = cmd->str;
	while (ptr_lst)
	{
		ft_putstr_fd(ft_is_var(ptr_lst->content, sh), cmd->fd_pipe_out);
		ptr_lst = ptr_lst->next;
		if (ptr_lst)
			write(cmd->fd_pipe_out, " ", 1);
		else if (!(cmd->flags && !ft_strcmp("-n", cmd->flags)))
			write(cmd->fd_pipe_out, "\n", 1);
	}
}

/*
**	voir si besoin de gere le old pwd dans l'env.
**	adapter avec l'ancien ft_cd.
*/

static void	ft_cd(t_cmd_lst *cmd, t_sh *sh)
{
	if (chdir(ft_is_var(cmd->str->content, sh)))
		return ;
		// ft_error(2, 0);
}

static void	commander_exec(t_cmd_lst *cmd, t_sh *sh)
{
	if (cmd->cmd_index == -1)
		exec_cmd(cmd, sh);
	else if (cmd->cmd_index == 0)
		ft_exit(sh);
	else if (cmd->cmd_index == 1)
		ft_echo(cmd, sh);
	else if (cmd->cmd_index == 2)
		ft_cd(cmd, sh);
	else if (cmd->cmd_index == 3)
		ft_pwd(cmd);
	else if (cmd->cmd_index == 4)
		ft_export(cmd, sh);
	else if (cmd->cmd_index == 5)
		ft_unset(cmd, sh);
	else if (cmd->cmd_index == 6)
		print_env(sh->env_lst, cmd->fd_pipe_out);
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
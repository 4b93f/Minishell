/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 14:24:58 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/30 19:53:31 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void pipe_engine(t_sh *sh)
{
	int piped[2];

	pipe(piped);
	sh->child_pid = fork();
	if (!sh->child_pid)
	{
		close(piped[1]);
		dup2(piped[0], 0);
		sh->fd_in = piped[0];
		return;
	}
	else
	{
		close(piped[0]);
		dup2(piped[1], 1);
		sh->fd_out = piped[1];
	}
}

void pipe_n_red(t_sh *sh)
{
	errno = 0;
	sh->ptr_cmd = sh->lst_cmd;
	while (sh->ptr_cmd)
	{	
		if (!sh->ptr_cmd->next)
			return;
		sh->ptr_cmd = sh->ptr_cmd->next;
		if (!ft_strcmp(sh->ptr_cmd->cmd, ">"))
		{
			if (!sh->ptr_cmd->next)
			{
				ft_putstr_fd("My Minishell: syntax error near unexpected token `newline'", 1);
				return ;
			}
			sh->ptr_cmd = sh->ptr_cmd->next;
			sh->fd_out = open(sh->ptr_cmd->cmd, O_CREAT | O_RDWR | O_TRUNC, 0777);
			if (error(sh->ptr_cmd->cmd, errno))
				return;
		}
		if (!ft_strcmp(sh->ptr_cmd->cmd, ">>"))
		{
			if (!sh->ptr_cmd->next)
			{
				ft_putstr_fd("My Minishell: syntax error near unexpected token `newline'", 2);
				return ;
			}
			sh->ptr_cmd = sh->ptr_cmd->next;
			sh->fd_out = open(sh->ptr_cmd->cmd, O_RDWR | O_APPEND | O_CREAT , 0777);
			if (error(sh->ptr_cmd->cmd, errno))
				return;
		}
		if (!ft_strcmp(sh->ptr_cmd->cmd, "<"))
		{
			if (!sh->ptr_cmd->next)
			{
				ft_putstr_fd("My Minishell: syntax error near unexpected token `newline'", 2);
				return ;
			}
			sh->ptr_cmd = sh->ptr_cmd->next;
			sh->fd_out = open(sh->ptr_cmd->cmd, O_RDONLY, 0777);
			if (error(sh->ptr_cmd->cmd, errno))
				return;
		}
		if (!ft_strcmp(sh->ptr_cmd->cmd, "|"))
		{
			pipe_engine(sh);
		}
	}
}
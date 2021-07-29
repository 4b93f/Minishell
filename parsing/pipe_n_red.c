/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 14:24:58 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/29 15:20:31 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

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
	}
}
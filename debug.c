/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 01:40:51 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/15 15:38:05 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dbg(t_sh *t)
{
	t_list		*ptr_lst;
	t_cmd_lst	*ptr_cmd;

	ptr_lst = t->arg_lst;
	ptr_cmd = t->cmd;
	// while (ptr_lst)
	// {
	// 	printf("Lst content:	[%s]\n", ptr_lst->content);
	// 	printf("Lst next:		[%p]\n\n", ptr_lst->next);
	// 	ptr_lst = ptr_lst->next;
	// }	
	while (ptr_cmd)
	{
		printf("Cmd index:			[%d]\n", ptr_cmd->cmd_index);
		printf("Cmd string:			[%s]\n", ptr_cmd->cmd_str);
		printf("Cmd flags:			[%s]\n\n", ptr_cmd->flags);
		printf("Cmd pipe in:		[%d]\n", ptr_cmd->pipe_in);
		printf("Cmd fd pipe in:		[%d]\n\n", ptr_cmd->fd_pipe_in);
		printf("Cmd pipe out:		[%d]\n", ptr_cmd->pipe_out);
		printf("Cmd fd pipe out:	[%d]\n\n", ptr_cmd->fd_pipe_out);
		printf("Cmd string:			[%p]\n", ptr_cmd->str);
		printf("Cmd next:			[%p]\n\n\n", ptr_cmd->next);
		ptr_cmd = ptr_cmd->next;
	}
}

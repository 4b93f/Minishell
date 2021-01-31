/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlstnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 02:44:47 by jsilance          #+#    #+#             */
/*   Updated: 2021/01/31 02:54:03 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cmd_cl.h"

t_cmd_lst	*ft_cmd_lstnew(void *str, void *flag, int index)
{
	t_cmd_lst	*ptr;

	if (!(ptr = (t_cmd_lst *)malloc(sizeof(t_cmd_lst))))
		return (NULL);
	ptr->str = str;
	ptr->cmd_str = NULL;
	ptr->flags = flag;
	ptr->cmd_index = index;
	ptr->pipe_in = 0;
	ptr->fd_pipe_in = -1;
	// ptr->fd_pipe_in = STDIN_FILENO;
	ptr->pipe_out = 0;
	ptr->fd_pipe_out = STDOUT_FILENO;
	ptr->pid = -1;
	ptr->next = NULL;
	return (ptr);
}

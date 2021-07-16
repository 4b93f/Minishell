/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:06:15 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/15 15:43:35 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include "executor.h"

void	ft_echo(t_cmd_lst *cmd, t_sh *sh)
{
	t_list	*ptr_lst;
	char	*ptr;

	ptr_lst = cmd->str;
	if (!ptr_lst && !(cmd->flags && !ft_strcmp("-n", cmd->flags)))
		write(cmd->fd_pipe_out, "\n", 1);
	while (ptr_lst)
	{
		ptr = ft_is_var(ptr_lst->content, sh);
		ptr = ft_backslash(ptr);
		ft_putstr_fd(ptr, cmd->fd_pipe_out);
		free(ptr);
		ptr_lst = ptr_lst->next;
		if (ptr_lst)
			write(cmd->fd_pipe_out, " ", 1);
		else if (!(cmd->flags && !ft_strncmp("-n", cmd->flags, 2)))
			write(cmd->fd_pipe_out, "\n", 1);
	}
	ft_set_free_env(sh, "?", ft_itoa(0));
}

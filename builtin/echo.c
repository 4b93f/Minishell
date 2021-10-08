/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 06:34:05 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/08 06:35:58 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

static void	echo_scan(t_sh *sh)
{
	sh->ptr_cmd = sh->lst_cmd;
	while (sh->ptr_cmd)
	{
		if ((!ft_strcmp(sh->ptr_cmd->cmd, "-n")))
			sh->flag_n = 1;
		sh->ptr_cmd = sh->ptr_cmd->next;
	}
	return ;
}

void	ft_echo(t_sh *sh)
{
	sh->ptr_cmd = sh->lst_cmd;
	echo_scan(sh);
	sh->ptr_cmd = sh->lst_cmd;
	sh->ptr_cmd = sh->ptr_cmd->next;
	if (sh->flag_n == 1)
		while (sh->ptr_cmd && (!ft_strcmp(sh->ptr_cmd->cmd, "-n")))
			sh->ptr_cmd = sh->ptr_cmd->next;
	while (sh->ptr_cmd && ft_strcmp(sh->ptr_cmd->cmd, "|"))
	{
		if (sh->ptr_cmd->type != ARG)
		{
			sh->ptr_cmd = sh->ptr_cmd->next;
			continue ;
		}
		ft_putstr_fd(sh->ptr_cmd->cmd, sh->fd_out);
		if (sh->ptr_cmd->next
			&& ft_strcmp(((t_lst_cmd *)sh->ptr_cmd->next)->cmd, "|"))
			ft_putstr_fd(" ", sh->fd_out);
		sh->ptr_cmd = sh->ptr_cmd->next;
	}
	if (sh->flag_n == 0)
		ft_putstr_fd("\n", sh->fd_out);
	sh->exit_code = 0;
	exit_code(sh, 0);
}

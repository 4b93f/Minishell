/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 06:34:05 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/12 16:49:44 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

int	isflag(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i++] == '-')
	{
		if (str[i] == 'n')
		{
			while (str[i] == 'n')
				i++;
			if (!str[i])
				return (1);
		}
		else
			return (0);
	}
	return (0);
}

static void	echo_scan(t_sh *sh)
{
	sh->ptr_cmd = sh->lst_cmd;
	while (sh->ptr_cmd)
	{
		if (isflag(sh->ptr_cmd->cmd))
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
		while (sh->ptr_cmd && isflag(sh->ptr_cmd->cmd))
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

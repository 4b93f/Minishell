
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 21:01:32 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/21 22:59:39 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

static void echo_scan(t_sh *sh)
{
	sh->ptr_cmd = sh->lst_cmd;
	while (sh->ptr_cmd->next)
	{
		if ((ft_strcmp(sh->ptr_cmd->cmd, "-n")))
			sh->flag_n = 1;	
		sh->ptr_cmd = sh->ptr_cmd->next;
	}
	return;
}

void ft_echo(t_sh *sh)
{
	sh->ptr_cmd = sh->lst_cmd;
	echo_scan(sh);
	sh->ptr_cmd = sh->lst_cmd;
	sh->ptr_cmd = sh->ptr_cmd->next;
	while (sh->ptr_cmd && ft_strcmp(sh->ptr_cmd->cmd, ";"))
	{
		ft_putstr_fd(sh->ptr_cmd->cmd, 1);
		ft_putstr_fd(" ", 1);
		sh->ptr_cmd = sh->ptr_cmd->next;
	}
	ft_putstr_fd("\n", 1);
	return;
}
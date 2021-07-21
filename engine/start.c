/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:05:25 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/21 22:29:59 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void start(t_sh *sh)
{
	sh->ptr_cmd = sh->lst_cmd;
	if (!ft_strcmp(sh->ptr_cmd->cmd, "echo"))
		ft_echo(sh);
	if (!ft_strcmp(sh->ptr_cmd->cmd, "env"))
		print_env(sh);
}
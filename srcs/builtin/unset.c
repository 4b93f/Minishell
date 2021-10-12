/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 22:45:16 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/08 09:48:27 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void	ft_unset(t_sh *sh)
{
	sh->ptr_cmd = sh->lst_cmd;
	sh->ptr_env = sh->lst_env;
	if (sh->ptr_cmd->next)
		sh->ptr_cmd = sh->ptr_cmd->next;
	if (!env_lstfinder(sh->ptr_env, sh->ptr_cmd->cmd))
		return ;
	env_lstdel(sh, sh->ptr_cmd->cmd);
}

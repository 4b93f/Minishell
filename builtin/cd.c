/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 17:47:03 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/25 00:10:42 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void ft_cd(t_sh *sh)
{
	int ret;
	sh->ptr_cmd = sh->lst_cmd;
	sh->ptr_env = sh->lst_env;
	ret = 0;
	
	if (sh->ptr_cmd->next)
		sh->ptr_cmd = sh->ptr_cmd->next;
	if (!ft_strcmp(sh->ptr_cmd->cmd, "~"))
		ret = chdir(env_lstfinder(sh->ptr_env, "HOME")->content);
}
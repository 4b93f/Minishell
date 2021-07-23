/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:18:27 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/23 23:11:49 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void	print_env(t_sh *sh)
{
	sh->ptr_env = sh->lst_env;
	while (sh->ptr_env)
	{
		if (sh->ptr_env)
		{
			ft_putstr_fd(sh->ptr_env->var, 1);
			write(1, "=", 1);
			ft_putstr_fd(sh->ptr_env->content, 1);
			write(1, "\n", 1);
		}
		sh->ptr_env = sh->ptr_env->next;
	}
}
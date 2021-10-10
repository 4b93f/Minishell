/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:07:15 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/10 18:06:14 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void	env_setup(t_sh *sh, char **env)
{
	env_tolst(env, sh, -1, 0);
	sh->ptr_env = sh->lst_env;
	if (!env_lstfinder(sh->ptr_env, "PWD"))
		env_lstaddback(&sh->ptr_env, env_lstnew(ft_strdup("PWD"),
				get_actual_path()));
	if (!env_lstfinder(sh->ptr_env, "_"))
		env_lstaddback(&sh->ptr_env, env_lstnew(ft_strdup("_"), NULL));
}

void	ft_free_env(t_sh *sh)
{
	if (sh->lst_env)
		env_lstclear(&sh->lst_env, free);
}

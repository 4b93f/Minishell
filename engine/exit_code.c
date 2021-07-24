/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 22:26:05 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/24 22:39:50 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void exit_code(t_sh *sh, int nbr)
{
	sh->ptr_env = sh->lst_env;
	if (!env_lstfinder(sh->ptr_env, "?"))
		env_lstaddback(&sh->ptr_env, env_lstnew("?", ft_itoa(nbr)));
	else if (env_lstdupe(sh, "?", ft_itoa(nbr)))
		env_lstedit(sh, "?", ft_itoa(nbr));
}
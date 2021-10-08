/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 22:26:05 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/08 09:50:35 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void	exit_code(t_sh *sh, int nbr)
{
	char	*n;

	n = ft_itoa(nbr);
	sh->ptr_env = sh->lst_env;
	if (!env_lstfinder(sh->ptr_env, "?"))
		env_lstaddback(&sh->ptr_env, env_lstnew("?", n));
	else if (env_lstdupe(sh, "?", n))
		env_lstedit(sh, "?", n);
	free(n);
}

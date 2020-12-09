/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:02:42 by chly-huc          #+#    #+#             */
/*   Updated: 2020/12/09 17:22:57 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh	ft_create_sh(void)
{
	t_sh sh;

	sh.env = NULL;
	sh.all_path = NULL;
	sh.built_in = NULL;
	sh.old_pwd = NULL;
	sh.actual_pwd = NULL;
	sh.tmp = NULL;
	sh.free = NULL;
	return (sh);
}

t_sh	*ft_malloc_sh(void)
{
	t_sh *malloc_sh;

	if (!(malloc_sh = malloc(sizeof(t_sh))))
		return (0);
	*malloc_sh = ft_create_sh();
	return (malloc_sh);
}

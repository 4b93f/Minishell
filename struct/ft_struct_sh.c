/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_sh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 18:55:15 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/21 22:24:50 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

#include "struct.h"

t_sh	ft_create_sh(void)
{
	t_sh sh;

	sh.all_path = NULL;
	sh.input_str = NULL;
	sh.flag_n = 0;
	sh.lst_env = NULL;
	sh.lst_cmd = NULL;
	sh.ptr_cmd = NULL;
	sh.ptr_env = NULL;
	return (sh);
}

t_sh	*ft_malloc_sh(void)
{
	t_sh *malloc_sh;

	if (!(malloc_sh = malloc(sizeof(t_sh))))
		return (NULL);
	*malloc_sh = ft_create_sh();
	return (malloc_sh);
}

void	ft_free_sh(t_sh *sh)
{
	if (!sh)
		return ;
	free(sh);
}
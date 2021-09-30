/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_sh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 18:55:15 by chly-huc          #+#    #+#             */
/*   Updated: 2021/09/30 16:37:07 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "struct.h"

t_sh	ft_create_sh(void)
{
	t_sh sh;

	sh.block_cmd = 0;
	sh.all_path = NULL;
	sh.input_str = NULL;
	sh.flag_n = 0;
	sh.lst_env = NULL;
	sh.lst_cmd = NULL;
	sh.ptr_cmd = NULL;
	sh.ptr_env = NULL;
	sh.fd_in = 0;
	sh.fd_out = 1;
	sh.fd_backup[0] = dup(0);
	sh.fd_backup[1] = dup(1);
	sh.stat = 0;
	sh.child_pid = 0;
	sh.dup = NULL;
	sh.exit_code = 0;
	sh.ret = 0;
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
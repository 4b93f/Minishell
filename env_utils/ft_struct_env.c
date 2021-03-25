/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:02:42 by chly-huc          #+#    #+#             */
/*   Updated: 2021/03/25 16:14:21 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_sh	ft_create_sh(void)
{
	t_sh sh;

	sh.all_path = NULL;
	sh.input_str = NULL;
	sh.arg_lst = NULL;
	sh.cmd = NULL;
	sh.env_lst = NULL;
	sh.parser.piped[0] = -1;
	sh.parser.piped[1] = -1;
	sh.parser.ptr_lst = NULL;
	sh.parser.ptr_cmd = NULL;
	sh.exec_env = NULL;
	sh.input_str = NULL;
	sh.save_str = NULL;
	sh.flag_c = 0;
	sh.cursor_i = 0;
	sh.cursor_j = 0;
	sh.tc_kl = NULL;
	sh.tc_kr = NULL;
	sh.tc_ku = NULL;
	sh.tc_kd = NULL;
	return (sh);
}

t_sh	*ft_malloc_sh(void)
{
	t_sh *malloc_sh;

	if (!(malloc_sh = malloc(sizeof(t_sh))))
		ft_error(MALLOC_ERROR, malloc_sh, 0);
	*malloc_sh = ft_create_sh();
	return (malloc_sh);
}

void	ft_free_sh(t_sh *sh)
{
	if (!sh)
		return ;
	sh_free(sh);
	if (sh->env_lst)
		ft_env_lstclear(&sh->env_lst, free);
	free(sh);
}

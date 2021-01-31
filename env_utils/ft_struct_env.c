/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:02:42 by chly-huc          #+#    #+#             */
/*   Updated: 2021/01/31 01:00:10 by jsilance         ###   ########.fr       */
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
	sh.ret_val = 0;
	return (sh);
}

t_sh	*ft_malloc_sh(void)
{
	t_sh *malloc_sh;

	if (!(malloc_sh = malloc(sizeof(t_sh))))
		ft_error(MALLOC_ERROR, malloc_sh);
	*malloc_sh = ft_create_sh();
	return (malloc_sh);
}

void	ft_free_sh(t_sh *sh)
{
	if (sh->all_path)
		free_tab(sh->all_path);
	if (sh->input_str)
		free(sh->input_str);
	if (sh->arg_lst)
		ft_lstclear(&sh->arg_lst, free);
	if (sh->cmd)
		ft_cmd_lstclear(&sh->cmd, free);
	if (sh->env_lst)
		ft_env_lstclear(&sh->env_lst, free);
	if (sh)
		free(sh);
}

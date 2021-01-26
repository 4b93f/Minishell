/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 00:46:45 by jsilance          #+#    #+#             */
/*   Updated: 2021/01/26 01:47:49 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	sh_free
**
**	Free the sh struct.
*/

void	sh_free(t_sh *sh)
{
	if (sh->input_str)
		free(sh->input_str);
	ft_lstclear(sh->arg_lst, free);
	ft_cmd_lstclear(sh->cmd, free);
	ft_env_lstclear(sh->env_lst, free);
}

int		ft_error(int error, int ret_val)
{
	if (error == 1)
		ft_putendl_fd("Commandnot found!", 2);
	if (error == 2)
		ft_putendl_fd("Change directory has failed!", 2);
	return (ret_val);
}
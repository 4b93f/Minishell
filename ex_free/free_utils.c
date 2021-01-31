/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 00:46:45 by jsilance          #+#    #+#             */
/*   Updated: 2021/01/31 01:00:04 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	sh_free
**
**	Free the sh struct.
*/

void	sh_free(t_sh *sh)
{
	if (sh->input_str)
		free(sh->input_str);
	ft_lstclear(&sh->arg_lst, free);
	ft_cmd_lstclear(&sh->cmd, free);
}

/*
** Free all malloc and more	
*/

void		ft_error(int ret, t_sh *sh)
{
	static char *error[] = {
	"Error with malloc\n"	
	};
	if (ret > 0)
		printf("%s", error[ret]);
	ft_free_sh(sh);
	exit(0);
}

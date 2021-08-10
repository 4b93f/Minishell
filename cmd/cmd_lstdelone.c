/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:52:28 by jsilance          #+#    #+#             */
/*   Updated: 2021/08/10 20:46:46 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	cmd_lstdelone(t_lst_cmd *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	if (lst->cmd)
		del(lst->cmd);
	free(lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:52:28 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/12 15:28:04 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	cmd_lstdelone(t_lst_cmd *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	cmd_lstclear(&lst->cmd, free);
	free(lst);
}

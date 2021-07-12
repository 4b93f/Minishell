/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 23:28:38 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/12 15:27:45 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	cmd_lstclear(t_lst_cmd **lst, void (*del)(void*))
{
	t_lst_cmd	*ptr;
	t_lst_cmd	*tmp;

	if (!lst || !*lst || !del)
		return ;
	tmp = NULL;
	ptr = *lst;
	while (ptr)
	{
		tmp = ptr->next;
		cmd_lstdelone(ptr, (*del));
		ptr = tmp;
	}
	*lst = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstlast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 04:51:36 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/12 15:14:14 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_lst_cmd	*cmd_last(t_lst_cmd *lst)
{
	t_lst_cmd	*ptr;

	ptr = NULL;
	while (lst)
	{
		ptr = lst;
		lst = lst->next;
	}
	return (ptr);
}

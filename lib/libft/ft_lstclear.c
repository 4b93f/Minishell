/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:38:58 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/22 16:41:14 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*first;
	t_list	*liste;

	if (*lst == NULL || lst == NULL)
		return ;
	first = *lst;
	liste = NULL;
	while (first)
	{
		if (first->next)
			liste = first->next;
		else
			liste = NULL;
		del(first);
		free(first);
		first = liste;
	}
	*lst = NULL;
}
/*
** Clear une liste chainée
*/

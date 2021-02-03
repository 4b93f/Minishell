/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:24:18 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/03 03:23:13 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *newcontent;

	newcontent = malloc(sizeof(t_list));
	if (!newcontent)
		return (0);
	newcontent->content = content;
	newcontent->next = NULL;
	return (newcontent);
}
/*
** Ajouter un nouvel élément
*/

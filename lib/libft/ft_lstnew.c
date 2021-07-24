/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:24:18 by chly-huc          #+#    #+#             */
/*   Updated: 2021/04/23 17:27:21 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newcontent;

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

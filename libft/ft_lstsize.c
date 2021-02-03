/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:04:24 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/03 03:22:15 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int i;

	i = 0;
	while (lst && ++i)
		lst = lst->next;
	return (i);
}
/*
** Compter le nombre d'éléments d'une chaine
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:33:32 by chly-huc          #+#    #+#             */
/*   Updated: 2021/04/27 14:57:46 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	if (tab)
		free(tab);
	tab = NULL;
	return (NULL);
}

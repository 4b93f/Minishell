/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:36:40 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/03 03:14:34 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*tab;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	i = ft_strlen((char*)s1) + ft_strlen((char*)s2) + 1;
	tab = malloc(i);
	if (!tab)
		return (NULL);
	j = -1;
	i = -1;
	while (s1[++i])
		tab[i] = s1[i];
	while (s2[++j])
		tab[j + i] = s2[j];
	tab[i + j] = '\0';
	return (tab);
}

/*
** Coller deux chaines de caractères ensembles
*/

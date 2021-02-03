/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:04:16 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/03 00:04:10 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	char	*source;
	int		i;

	if (!s)
		return (NULL);
	source = (char *)s;
	if (!((dest = (char *)malloc(sizeof(char) * (ft_strlen(source) + 1)))))
		return (0);
	i = 0;
	while (source[i])
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
** Créer un chaine de caractère avec malloc
*/

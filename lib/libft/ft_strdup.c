/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:04:16 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/21 22:36:40 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	char	*source;
	int		i;

	source = (char *)s;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(source) + 1));
	if (!dest)
		return (0);
	i = 0;
	while (source[i])
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	//free((char *)s);
	return (dest);
}

/*
** Créer un chaine de caractère avec malloc
*/

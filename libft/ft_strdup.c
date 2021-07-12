/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:04:16 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/26 16:06:21 by chly-huc         ###   ########.fr       */
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
	dest = malloc(ft_strlen(source) + 1);
	if (!dest)
		return (0);
	i = -1;
	while (source[++i])
		dest[i] = source[i];
	dest[i] = '\0';
	return (dest);
}

/*
** Créer un chaine de caractère avec malloc
*/

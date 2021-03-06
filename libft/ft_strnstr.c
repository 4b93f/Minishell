/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:06:14 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/16 22:49:04 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = -1;
	if (!needle[0])
		return ((char *)haystack);
	j = 0;
	while (haystack[++i] && i < len)
		while (haystack[i + j] == needle[j] && i + j < len)
			if (!needle[++j])
				return (&((char *)haystack)[i]);
	return (NULL);
}

/*
** Cherche aiguilles dans foin tant que len > 0
*/

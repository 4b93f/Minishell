/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 09:51:28 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/03 03:20:12 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	if (n <= 0)
		return (0);
	i = -1;
	str = (unsigned char *)s;
	while (++i < n)
		if (str[i] == (unsigned char)c)
			return (&str[i]);
	return (0);
}
/*
** Chercher "c" dans la ZONE MEMOIRE de la chaine de caractère tant que n > 0
*/

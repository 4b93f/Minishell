/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 00:23:54 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/03 03:20:03 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = -1;
	while (n-- > 0)
		if (ss1[++i] != ss2[i])
			return (ss1[i] - ss2[i]);
	return (0);
}
/*
** Compare les n octets de la ZONE MEMOIRE de S1 et S2 tant que s1 = s2
*/

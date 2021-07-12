/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:09:51 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/03 03:09:52 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	int				j;
	unsigned char	*ssrc;

	j = 0;
	ssrc = (unsigned char *)src;
	while (ssrc[j])
		j++;
	if (size == 0)
		return (j);
	i = -1;
	while (ssrc[++i] && i < size - 1)
		dest[i] = ssrc[i];
	dest[i] = '\0';
	return (j);
}
/*
** Copie size caractère de SRC dans DEST sans ce soucier
** de la taille de DEST
*/

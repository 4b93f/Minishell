/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 12:39:23 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/15 15:19:45 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	*str;
	int				size;

	i = 0;
	str = (unsigned char *)s;
	size = ft_strlen((char *)str);
	while (size != 0)
	{
		if (str[size] != c)
			size--;
		else
			return ((char *)str + size);
	}
	if (str[size] == c)
		return ((char *)&str[i]);
	return (NULL);
}
/*
**  Localise en partant de la fin le caractère "c" dans S
*/

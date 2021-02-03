/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 12:17:09 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/03 03:16:19 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (str && str[i])
		if (str[i++] == c)
			return (str + i);
	if (str && str[i] == c)
		return (str + i);
	return (NULL);
}
/*
** Cherche le caractére "c" dans la chaine caractére S
*/

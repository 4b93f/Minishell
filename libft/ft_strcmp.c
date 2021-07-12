/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 21:49:38 by jsilance          #+#    #+#             */
/*   Updated: 2021/05/25 23:25:01 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	count;
	
	count = -1;
	while (s1 && s2 && s1[++count] && s2[count])
		if ((unsigned char)s1[count] != (unsigned char)s2[count])
			return ((unsigned char)s1[count] - (unsigned char)s2[count]);
	if (s1 && s2 && (unsigned char)s1[count] != (unsigned char)s2[count])
		return ((unsigned char)s1[count] - (unsigned char)s2[count]);
	return (0);
}

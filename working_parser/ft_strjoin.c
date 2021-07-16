/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:36:28 by jehaenec          #+#    #+#             */
/*   Updated: 2021/07/15 14:34:06 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	p = dst;
	while (*s1)
	{
		*dst = *(char *)s1++;
		dst++;
	}
	while (*s2)
	{
		*dst = *(char *)s2++;
		dst++;
	}
	*dst = 0;
	return (p);
}

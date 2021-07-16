/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:26:51 by jehaenec          #+#    #+#             */
/*   Updated: 2021/07/15 14:36:51 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ft_isset(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*dst;
	char	*ret;
	char	*tmp;

	if (!s1 || !set || set == s1)
		return (NULL);
	i = ft_strlen(s1);
	i--;
	tmp = (char *)s1;
	while (i >= 0 && ft_isset(s1[i], (char *)set))
		i--;
	while (i >= 0 && ft_isset(*tmp++, (char *)set))
		i--;
	dst = (char *)malloc(sizeof(char) * (i + 2));
	if (!dst)
		return (NULL);
	ret = dst;
	tmp--;
	if (i > 0)
		while (i-- >= 0)
			*dst++ = *tmp++;
	*dst = '\0';
	return (ret);
}

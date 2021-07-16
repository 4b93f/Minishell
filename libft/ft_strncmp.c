/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 12:53:47 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/15 15:18:33 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = 0;
	if (!s1 || !s2)
		return (1);
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (n--)
	{
		if ((ss1[i] != ss2[i] || !ss1[i] || !ss2[i]))
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (0);
}

/*
** Compare n caractères entre S1 et S2
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:45:55 by jehaenec          #+#    #+#             */
/*   Updated: 2021/07/15 14:32:31 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		n;

	n = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (0);
	ft_strcpy(dup, s1);
	return (dup);
}

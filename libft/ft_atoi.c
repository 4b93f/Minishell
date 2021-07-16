/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:20:02 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/15 15:56:36 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	*nbr;

	if (!str || !*str)
		return (0);
	nbr = (long [3]){0, 0, 0};
	while ((str[nbr[1]] >= 9 && str[nbr[1]] <= 13) || str[nbr[1]] == 32)
		nbr[1]++;
	nbr[0] = (str && str[nbr[1]] == '-');
	nbr[1] += (nbr[0] == 1 || str[nbr[1]] == '+');
	while (ft_isdigit(str[nbr[1]]))
	{
		nbr[2] = (nbr[2] * 10) + (str[nbr[1]++] - 48);
		if (nbr[2] < 0)
		{
			if (nbr[0])
				return (-1);
			return (0);
		}
	}
	if (nbr[0] == 1)
		return (-nbr[2]);
	return (nbr[2]);
}

long long	ft_atol(const char *str)
{
	long long	*nbr;

	if (!str || !*str)
		return (0);
	nbr = (long long [3]){0, 0, 0};
	while ((str[nbr[1]] >= 9 && str[nbr[1]] <= 13) || str[nbr[1]] == 32)
		nbr[1]++;
	nbr[0] = (str && str[nbr[1]] == '-');
	nbr[1] += (nbr[0] == 1 || str[nbr[1]] == '+');
	while (ft_isdigit(str[nbr[1]]))
	{
		nbr[2] = (nbr[2] * 10) + (str[nbr[1]++] - 48);
		if (nbr[2] < 0)
		{
			if (nbr[0])
				return (-1);
			return (0);
		}
	}
	if (nbr[0] == 1)
		return (-nbr[2]);
	return (nbr[2]);
}

/*
** Changer une chaine de caractère en "nombre"
*/

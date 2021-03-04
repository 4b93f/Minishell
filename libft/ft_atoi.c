/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:20:02 by chly-huc          #+#    #+#             */
/*   Updated: 2021/03/04 00:49:28 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		neg;
	int		cou;
	long	nbr;

	if (!str || !*str || (neg = 0))
		return (0);
	nbr = 0;
	cou = 0;
	while (str[cou] == '\t' || str[cou] == '\n' || str[cou] == '\r' ||
		str[cou] == '\v' || str[cou] == '\f' || str[cou] == ' ')
		cou++;
	neg = (str && str[cou] == '-');
	cou += (neg == 1 || str[cou] == '+');
	while (ft_isdigit(str[cou]))
		if ((nbr = (nbr * 10) + (str[cou++] - 48)) < 0)
			return ((neg) ? -1 : 0);
	return ((neg == 1) ? -nbr : nbr);
}

long	ft_atol(const char *str)
{
	int			neg;
	int			cou;
	long long	nbr;

	if (!str || !*str || (neg = 0))
		return (0);
	nbr = 0;
	cou = 0;
	while (str[cou] == '\t' || str[cou] == '\n' || str[cou] == '\r' ||
		str[cou] == '\v' || str[cou] == '\f' || str[cou] == ' ')
		cou++;
	neg = (str && str[cou] == '-');
	cou += (neg == 1 || str[cou] == '+');
	while (ft_isdigit(str[cou]))
		if ((nbr = (nbr * 10) + (str[cou++] - 48)) < 0)
			return ((neg) ? -1 : 0);
	return ((neg == 1) ? -nbr : nbr);
}

/*
** Changer une chaine de caractère en "nombre"
*/

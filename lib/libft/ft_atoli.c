/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoli.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:15:27 by chly-huc          #+#    #+#             */
/*   Updated: 2021/04/27 20:00:59 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	result_atoli(int sign, long res)
{
	if (sign > 0)
		return (res);
	else
		return (-res);
}

long	ft_atoli(const char *str)
{
	long		i;
	long long	res;
	int			sign;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = sign * (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
		if (res < 0)
		{
			if (sign > 0)
				return (-1);
			else
				return (0);
		}
	}
	return (result_atoli(sign, res));
}

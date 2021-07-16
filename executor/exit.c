/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:24:25 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/15 16:07:16 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include "executor.h"

static int	ft_str_digit(char *str)
{
	while (str && ft_isspace(*str))
		str++;
	if (str && (*str == '+' || *str == '-'))
		str++;
	if (!ft_strcmp(str, "-0"))
		return (0);
	return (1);
}

static char	*ft_after_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == 32 || str[i] == '\t')
		i++;
	if (str[i])
		return (&str[i]);
	return (NULL);
}

static int	ft_long_verif(const char *str)
{
	int			cou;
	long long	nbr;

	if (!str || !*str)
		return (1);
	nbr = 0;
	cou = 0;
	if (!ft_strcmp(str, "-9223372036854775808"))
		return (1);
	while ((str[cou] >= 9 && str[cou] <= 13) || str[cou] == ' ')
		cou++;
	cou += (str[cou] == '-' || str[cou] == '+');
	while (ft_isdigit(str[cou]))
	{
		nbr = (nbr * 10) + (str[cou++] - 48);
		if (nbr < 0)
			return (0);
	}
	if (nbr & (unsigned long long)1 << 63)
		return (0);
	return (1);
}

void	ft_exit(t_cmd_lst *cmd, t_sh *sh)
{
	unsigned long long	ret;
	char				*str;

	str = NULL;
	ret = 0;
	if (cmd->str)
	{
		cmd->str->content = rm_guim(cmd->str->content);
		str = cmd->str->content;
	}
	if (str && ft_long_verif(str) && (ft_atol(str) || ft_isdigit(str[0])
			|| ft_isdigit(str[1])))
		ret = ft_atol(str);
	if (!ft_strcmp(str, "-9223372036854775808"))
		ret = 0;
	if (str && !ft_long_verif(str) && ft_strlen(str) >= 20 + (str[0] == '-'))
		ft_error_two(str, sh, 255);
	else if ((ft_long_verif(str) && ft_after_digit(str))
		|| !ft_long_verif(str)
		|| (ft_strlen(str) == 20 && ret == 0 && str[0] != '-'))
		ft_error_two(str, sh, 255);
	else if (cmd->str && cmd->str->next)
		ft_error(EXIT_TO_MANY_ARG, sh, 1);
	ft_free_sh(sh);
	exit(ret);
}

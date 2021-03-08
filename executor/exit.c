/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:24:25 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/08 13:16:24 by jsilance         ###   ########.fr       */
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

void	ft_exit(t_cmd_lst *cmd, t_sh *sh)
{
	int		i;
	int		ret;
	char	*str;

	str = NULL;
	i = 0;
	ret = 0;
	if (cmd->str)
	{
		cmd->str->content = rm_guim(cmd->str->content);
		str = cmd->str->content;
	}
	if (str && ft_strcmp("-9223372036854775808", str) && (ft_atol(str) || ft_isdigit(str[0]) || ft_isdigit(str[1])))
		ret = ft_atol(str);
	if (str && (ret == -1 || ret == 0) && ft_strlen(str) >= 20 + (str[0] == '-'))
		ft_error_two(str, sh, 255);
	else if ((cmd->str && ret >= 0 && str[0] == '-' && ret < 0))
		ft_error(EXIT_ILLEGAL, sh, ret);
	else if (ft_strcmp("-9223372036854775808", str) != 0 && ((cmd->str && ft_strcmp("9223372036854775807", str) <= 0 && !ret) || ft_after_digit(str)))
		ft_error_two(str, sh, 255);
	else if (cmd->str && cmd->str->next)
		ft_error(EXIT_TO_MANY_ARG, sh, 1);
	ft_free_sh(sh);
	exit(ret);
}

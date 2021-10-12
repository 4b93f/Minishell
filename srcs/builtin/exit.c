/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 17:23:56 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/12 16:54:51 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

long long	result_strtoll(long long sign, long long res)
{
	if (sign > 0)
		return (res);
	else
		return (-res);
}

long long	ft_strtoll(char *str, int *toolong, int i)
{
	long long	res;
	int			sign;

	sign = 1;
	res = 0;
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
			*toolong = 1;
			if (sign > 0)
				return (-1);
			else
				return (0);
		}
	}
	return (result_strtoll(sign, res));
}

int	verif(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

void	exit_ret(t_sh *sh, long long *ret)
{
	int	toolong;

	toolong = 0;
	*ret = ft_strtoll(sh->ptr_cmd->cmd, &toolong, 0);
	if (toolong == 1)
	{
		ft_putstr_fd("My Minishell: exit: ", 1);
		ft_putstr_fd(sh->ptr_cmd->cmd, 1);
		ft_putendl_fd(": numeric argument required", 1);
	}
	if (ft_strlen(sh->ptr_cmd->cmd) >= 19 && (ft_strcmp(sh->ptr_cmd->cmd,
				"9223372036854775807") > 0))
		*ret = 2;
	if (ft_strlen(sh->ptr_cmd->cmd) >= 20 && (!ft_strcmp(sh->ptr_cmd->cmd,
				"-9223372036854775808") || (ft_strlen(sh->ptr_cmd->cmd)
				>= 19 && (!ft_strcmp(sh->ptr_cmd->cmd,
						"9223372036854775807")))))
		*ret = 0;
	else if (*ret == -1 || (*ret == 0 && !verif(sh->ptr_cmd->cmd)))
		*ret = 2;
}

void	ft_exit(t_sh *sh)
{
	long long	ret;

	ret = 1;
	errno = 0;
	sh->ptr_cmd = sh->lst_cmd;
	if (sh->ptr_cmd->next)
		sh->ptr_cmd = sh->ptr_cmd->next;
	ft_putendl_fd("exit", 1);
	if (sh->ptr_cmd->next && ft_strcmp(sh->ptr_cmd->cmd, "|"))
	{
		errno = EXIT_ARG;
		error(sh, "exit");
	}
	else
		exit_ret(sh, &ret);
	ft_free_env(sh);
	sh_free(sh);
	ft_free_sh(sh);
	exit(ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 15:01:52 by chly-huc          #+#    #+#             */
/*   Updated: 2021/09/16 13:11:33 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

int error(t_sh *sh, char *str)
{
	if (errno == CMD_NOT_FOND)
	{
		ft_putstr_fd("My Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit_code(sh, 2);
		return (2);
	}
	if (errno == PERM_DENIED)
	{
		
		ft_putstr_fd("My Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (1);
	}
	if (errno == IS_DIRECTORY)
	{
		ft_putstr_fd("My Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (1);
	}
	if (errno == FORK)
	{
		ft_putstr_fd("My Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" retry: Resource temporarily unavailable\n", 2);
		return (1);
	}
	if (errno == UNV_ID)
	{
		ft_putstr_fd("My Minishell: ", 2);
		ft_putstr_fd("`", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	if (errno == EXIT_ARG)
	{
		ft_putstr_fd("My Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": too many arguments\n", 2);
		return (1);
	}
	return (0);
}
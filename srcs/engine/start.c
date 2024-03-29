/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:05:25 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/12 18:21:54 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void	start(t_sh *sh)
{
	char	*file;
	char	**envp;
	char	**argp;

	file = NULL;
	envp = NULL;
	argp = NULL;
	if (!ft_strcmp(sh->ptr_cmd->cmd, "echo"))
		ft_echo(sh);
	else if (!ft_strcmp(sh->ptr_cmd->cmd, "env"))
		print_env(sh);
	else if (!ft_strcmp(sh->ptr_cmd->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(sh->ptr_cmd->cmd, "exit"))
		ft_exit(sh);
	else if (!ft_strcmp(sh->ptr_cmd->cmd, "export"))
		ft_export(sh);
	else if (!ft_strcmp(sh->ptr_cmd->cmd, "unset"))
		ft_unset(sh);
	else if (!ft_strcmp(sh->ptr_cmd->cmd, "cd"))
		ft_cd(sh);
	else
		exec_cmd(sh, file, envp, argp);
	sh->block_cmd = 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:35:03 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/15 15:29:18 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include "executor.h"

void	ft_pwd(t_cmd_lst *cmd, t_sh *sh)
{
	char	*buf;

	buf = get_actual_path();
	if (!buf)
		return ;
	ft_putstr_fd(buf, cmd->fd_pipe_out);
	ft_putstr_fd("\n", cmd->fd_pipe_out);
	free(buf);
	free(env_lst_finder(sh->env_lst, "?")->content);
	env_lst_finder(sh->env_lst, "?")->content = ft_itoa(0);
}

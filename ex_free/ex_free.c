/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:52:00 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/08 10:22:14 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void	ft_reset(t_sh *sh)
{
	if (sh->fd_in != -1)
		close(sh->fd_in);
	if (sh->fd_out != -1)
		close(sh->fd_out);
	sh->fd_in = -1;
	sh->fd_out = -1;
	dup2(sh->fd_backup[0], 0);
	dup2(sh->fd_backup[1], 1);
}

void	sh_free(t_sh *sh)
{
	if (sh->lst_cmd)
		cmd_lstclear(&sh->lst_cmd, free);
	free_tab(sh->all_path);
	free(sh->input_str);
	sh->all_path = NULL;
	sh->flag_n = 0;
	dup2(sh->fd_backup[0], 0);
	dup2(sh->fd_backup[1], 1);
	sh->ptr_cmd = sh->lst_cmd;
	if (sh->fd_in != 0)
		close(sh->fd_in);
	if (sh->fd_out != 1)
		close(sh->fd_out);
	sh->fd_in = 0;
	sh->fd_out = 1;
	sh->block_cmd = 0;
}

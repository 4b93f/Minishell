/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 14:24:58 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/11 23:27:46 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

int	ft_pipe(t_sh *sh)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return(2);
	pid = fork();
	if (pid < 0)
		return(2);
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		sh->fd_in = fd[0];
		sh->stat = 1;
		return (1);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		sh->fd_out = fd[1];
		sh->stat = 2;
		return (2);
	}
}

void	check_sep(t_sh *sh, t_lst_cmd *token, t_lst_cmd *prev, int prev_type)
{
	if (sh->block_cmd == 0 && prev && prev_type == RIGHT)
		red_right(sh, token);
	if (sh->block_cmd == 0 && prev && prev_type == DRIGHT)
		red_dright(sh, token);
	if (sh->block_cmd == 0 && prev && prev_type == LEFT)
		red_left(sh, token);
	if (sh->block_cmd == 0 && prev && prev_type == DLEFT)
		red_dleft(sh, token);
}

void	exec(t_sh *sh, t_lst_cmd *token)
{
	int			prev_type;
	pid_t		pid;	
	t_lst_cmd	*next;
	t_lst_cmd	*prev;

	prev_type = 0;
	pid = 0;
	next = next_sep(token);
	prev = previous_sep(sh, token);
	prev_type = previous_type(sh, token);
	check_sep(sh, token, prev, prev_type);
	if (sh->block_cmd == 0 && prev && prev_type == PIPE)
		pid = ft_pipe(sh);
	if (sh->block_cmd == 0 && next && pid != 1)
	{
		sh->ptr_cmd = next;
		exec(sh, next);
	}
	if (sh->block_cmd == 0 && (!prev || prev_type == PIPE) && pid != 2)
	{
		sh->ptr_cmd = token;
		start(sh);
	}
}

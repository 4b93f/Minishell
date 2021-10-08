/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 13:42:33 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/08 13:46:24 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void	red_right(t_sh *sh, t_lst_cmd *token)
{
	errno = 0;
	sh->ptr_cmd = token;
	if (!sh->ptr_cmd)
	{
		ft_putstr_fd("My Minishell: syntax error near", 2);
		ft_putstr_fd("unexpected token`newline'", 2);
	}
	else if (str_spechar(sh->ptr_cmd->cmd))
	{
		errno = SYNTAX_ERROR;
		error(sh, sh->ptr_cmd->cmd);
		sh->block_cmd = 1;
		exit_code(sh, 0);
		return ;
	}
	if (sh->fd_out != 1)
		close(sh->fd_out);
	sh->fd_out = open(sh->ptr_cmd->cmd, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (error(sh, sh->ptr_cmd->cmd))
		return ;
}

void	red_dright(t_sh *sh, t_lst_cmd *token)
{
	errno = 0;
	sh->ptr_cmd = token;
	if (!sh->ptr_cmd)
	{
		ft_putstr_fd("My Minishell: syntax error near", 2);
		ft_putstr_fd("unexpected token`newline'", 2);
		return ;
	}
	else if (str_spechar(sh->ptr_cmd->cmd))
	{
		errno = SYNTAX_ERROR;
		error(sh, sh->ptr_cmd->cmd);
		sh->block_cmd = 1;
		exit_code(sh, 0);
		return ;
	}
	if (sh->fd_out != 1)
		close(sh->fd_out);
	sh->fd_out = open(sh->ptr_cmd->cmd, O_RDWR
			| O_APPEND | O_CREAT, 0777);
	if (error(sh, sh->ptr_cmd->cmd))
		return ;
}

void	red_left(t_sh *sh, t_lst_cmd *token)
{
	errno = 0;
	sh->ptr_cmd = token;
	if (!sh->ptr_cmd)
	{
		ft_putstr_fd("My Minishell: syntax error near", 2);
		ft_putstr_fd("unexpected token`newline'", 2);
		return ;
	}
	else if (str_spechar(sh->ptr_cmd->cmd))
	{
		errno = SYNTAX_ERROR;
		error(sh, sh->ptr_cmd->cmd);
		sh->block_cmd = 1;
		exit_code(sh, 0);
		return ;
	}
	if (sh->fd_in != 0)
		close(sh->fd_out);
	sh->fd_in = open(sh->ptr_cmd->cmd, O_RDONLY, 0777);
	dup2(sh->fd_in, 0);
	if (errno)
		ft_putendl_fd(strerror(errno), 2);
}

void	red_dleft(t_sh *sh, t_lst_cmd *token)
{
	int		pid;
	char	*tmp;

	errno = 0;
	tmp = NULL;
	pid = 0;
	sh->ptr_cmd = token;
	if (!sh->ptr_cmd)
	{
		ft_putstr_fd("My Minishell: syntax error near", 2);
		ft_putstr_fd("unexpected token`newline'", 2);
		return ;
	}
	else if (str_spechar(sh->ptr_cmd->cmd))
	{
		errno = SYNTAX_ERROR;
		error(sh, sh->ptr_cmd->cmd);
		sh->block_cmd = 1;
		exit_code(sh, 0);
		return ;
	}
	if (errno)
		ft_putendl_fd(strerror(errno), 2);
	chdir("/tmp");
	sh->fd_in = open("tmp_file", O_CREAT | O_RDWR, 0777);
	red_forked(sh, pid, tmp);
}

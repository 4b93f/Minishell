/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 23:28:35 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/16 21:52:33 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	set_pipe(t_sh *sh)
{
	pipe(sh->parser.piped);
	sh->parser.ptr_cmd->pipe_out = PIPE;
	sh->parser.ptr_cmd->fd_pipe_out = sh->parser.piped[1];
	sh->parser.ptr_lst = sh->parser.ptr_lst->next;
	if (!sh->parser.ptr_lst)
		return (0);
	else
		return (1);
}

/*
** Write the content of the file in the stdin.
*/

static int	set_left_red(t_sh *sh)
{
	int	ret;

	sh->parser.ptr_cmd->pipe_in = S_LEFT_RED;
	sh->parser.ptr_lst = sh->parser.ptr_lst->next;
	if (!sh->parser.ptr_lst)
		return (0);
	if (sh->parser.ptr_lst && !sep_checker(sh->parser.ptr_lst->content))
	{
		ft_lstadd_back(&sh->parser.ptr_cmd->red_file,
			ft_lstnew(ft_strdup(sh->parser.ptr_lst->content)));
		sh->parser.ptr_lst = sh->parser.ptr_lst->next;
	}
	ret = (lex_to_cmdstr(sh));
	if (ret > -1)
		return (ret);
	return (1);
}

static int	set_simple_red(t_sh *sh)
{
	int	ret;

	if (sh->parser.ptr_lst && !ft_strcmp(sh->parser.ptr_lst->content, ">"))
	{
		sh->parser.ptr_cmd->pipe_out = S_RIGHT_RED;
		sh->parser.ptr_lst = sh->parser.ptr_lst->next;
		if (!sh->parser.ptr_lst)
			return (0);
		if (sh->parser.ptr_lst && !sep_checker(sh->parser.ptr_lst->content))
		{
			ft_lstadd_back(&sh->parser.ptr_cmd->red_file,
				ft_lstnew(ft_strdup(sh->parser.ptr_lst->content)));
			sh->parser.ptr_lst = sh->parser.ptr_lst->next;
		}
		ret = (lex_to_cmdstr(sh));
		if (ret > -1)
			return (ret);
		return (1);
	}
	return (1);
}

static int	set_double_red(t_sh *sh)
{
	int	ret;

	sh->parser.ptr_cmd->pipe_out = D_RIGHT_RED;
	sh->parser.ptr_lst = sh->parser.ptr_lst->next;
	if (!sh->parser.ptr_lst)
		return (0);
	if (sh->parser.ptr_lst && !sep_checker(sh->parser.ptr_lst->content))
	{
		ft_lstadd_back(&sh->parser.ptr_cmd->red_file,
			ft_lstnew(ft_strdup(sh->parser.ptr_lst->content)));
		sh->parser.ptr_lst = sh->parser.ptr_lst->next;
	}
	ret = (lex_to_cmdstr(sh));
	if (ret > -1)
		return (ret);
	return (1);
}

int	set_pipe_red(t_sh *sh)
{
	if (sh->parser.ptr_lst && !ft_strcmp(sh->parser.ptr_lst->content, "|"))
		return (set_pipe(sh));
	if (sh->parser.ptr_lst && !ft_strcmp(sh->parser.ptr_lst->content, ">>"))
		return (set_double_red(sh));
	if (sh->parser.ptr_lst && !ft_strcmp(sh->parser.ptr_lst->content, ">"))
		return (set_simple_red(sh));
	if (sh->parser.ptr_lst && !ft_strcmp(sh->parser.ptr_lst->content, "<"))
		return (set_left_red(sh));
	return (-1);
}

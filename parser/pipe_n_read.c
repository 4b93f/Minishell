/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 23:28:35 by jsilance          #+#    #+#             */
/*   Updated: 2021/02/14 23:53:43 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	set_pipe(t_sh *sh)
{
	pipe(sh->parser.piped);
	sh->parser.ptr_cmd->pipe_out = 1;
	sh->parser.ptr_cmd->fd_pipe_out = sh->parser.piped[1];
	if (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next))
		return (0);
	else
		return (1);
}

static int	set_left_red(t_sh *sh)
{
	int	ret;

	sh->parser.ptr_cmd->pipe_out = 4;
	if (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next))
		return (0) ;
	if (sh->parser.ptr_lst && !sep_checker(sh->parser.ptr_lst->content))
	{
		ft_lstadd_back(&sh->parser.ptr_cmd->red_file, ft_lstnew(ft_strdup(sh->parser.ptr_lst->content)));
		sh->parser.ptr_lst = sh->parser.ptr_lst->next;
	}
	if (ret = lex_to_cmdstr(sh) > -1)
		return (ret);
	return (1);
}

static int	set_simple_red(t_sh *sh)
{
	int	ret;

	if (sh->parser.ptr_lst && !ft_strcmp(sh->parser.ptr_lst->content, ">"))
	{
		sh->parser.ptr_cmd->pipe_out = 2;
		
		if (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next))
			return (0);
		if (sh->parser.ptr_lst && !sep_checker(sh->parser.ptr_lst->content))
		{
			ft_lstadd_back(&sh->parser.ptr_cmd->red_file, ft_lstnew(ft_strdup(sh->parser.ptr_lst->content)));
			sh->parser.ptr_lst = sh->parser.ptr_lst->next;
		}
		if (ret = lex_to_cmdstr(sh) > -1)
			return (ret);
		return (1);
	}
}

static int	set_double_red(t_sh *sh)
{
	int	ret;

	sh->parser.ptr_cmd->pipe_out = 3;
	if (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next))
		return (0);
	if (sh->parser.ptr_lst && !sep_checker(sh->parser.ptr_lst->content))
	{
		ft_lstadd_back(&sh->parser.ptr_cmd->red_file, ft_lstnew(ft_strdup(sh->parser.ptr_lst->content)));
		sh->parser.ptr_lst = sh->parser.ptr_lst->next;
	}
	if (ret = lex_to_cmdstr(sh) > -1)
		return (ret);
	return (1);
}

int			set_pipe_red(t_sh *sh)
{
	if (sh->parser.ptr_lst && !ft_strcmp(sh->parser.ptr_lst->content, "|"))
		return(set_pipe(sh));
	if (sh->parser.ptr_lst && !ft_strcmp(sh->parser.ptr_lst->content, ">>"))
		return(set_double_red(sh));
	if (sh->parser.ptr_lst && !ft_strcmp(sh->parser.ptr_lst->content, ">"))
		return(set_simple_red(sh));
	if (sh->parser.ptr_lst && !ft_strcmp(sh->parser.ptr_lst->content, "<"))
		return(set_left_red(sh));
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 01:53:26 by jsilance          #+#    #+#             */
/*   Updated: 2021/01/17 04:47:15 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	cmd_flag_check(char *str)
{
	if (!ft_strcmp("-n", str))
		return (1);
	return (0);
}

static int	cmd_chekcer(char *str)
{
	if (str)
	{
		if (!ft_strcmp("exit", str))
			return (0);
		else if (!ft_strcmp("echo", str))
			return (1);
		else if (!ft_strcmp("cd", str))
			return (2);
		else if (!ft_strcmp("pwd", str))
			return (3);
		else if (!ft_strcmp("export", str))
			return (4);
		else if (!ft_strcmp("unset", str))
			return (5);
		else if (!ft_strcmp("env", str))
			return (6);
		else if (!ft_strcmp("help", str))
			return (7);
	}
	// return (ft_error(1, -1));
	return (-1);
}

/*
**	Peut-etre ajouter un sep index.
*/

static int	sep_checker(char *str)
{
	if (!ft_strcmp(str, ">") || 
		!ft_strcmp(str, ">>") ||
		!ft_strcmp(str, "<") ||
		!ft_strcmp(str, "<<") ||
		!ft_strcmp(str, "|") ||
		!ft_strcmp(str, "||") ||
		!ft_strcmp(str, ";") ||
		!ft_strcmp(str, "&&"))
		return (1);
	return (0);
}

/*
**	cmd_index -1 --> error
**	cmd_index  0 --> exit
**	cmd_index  1 --> echo
**	cmd_index  2 --> cd
**	cmd_index  3 --> pwd
**	cmd_index  4 --> export
**	cmd_index  5 --> unset
**	cmd_index  6 --> env
**	cmd_index  7 --> help
*/

static int	chain_maker(t_sarg *t)
{
	t_list		*ptr;
	t_cmd_lst	*cmd_ptr;
	int			piped[2];
	
	piped[0] = -1;
	piped[1] = -1;
	ptr = t->arg_lst;
	cmd_ptr = NULL;
	while(ptr)
	{
		if (!ft_strcmp(ptr->content, ";") && (ptr = ptr->next))
			continue ;
		if (!ptr)
			continue ;
		ft_cmd_lstadd_back(&t->cmd, ft_cmd_lstnew(NULL, NULL,
			cmd_chekcer(ptr->content)));
		cmd_ptr = ft_cmd_lstlast(t->cmd);
		if (piped[0] > -1)
		{
			cmd_ptr->fd_pipe_in = piped[0];
			cmd_ptr->pipe_in = 1;
			piped[0] = -1;
		}
		if (!(ptr = ptr->next) || !ft_strcmp(ptr->content, ";"))
			continue ;
		if (ptr && cmd_ptr->cmd_index == 1 && cmd_flag_check(ptr->content))
		{
			cmd_ptr->flags = ft_strdup(ptr->content);
			if (!(ptr = ptr->next) || !ft_strcmp(ptr->content, ";"))
				break ;
		}
		if (ptr && !ft_strcmp(ptr->content, "|"))
		{
			pipe(piped);
			cmd_ptr->pipe_out = 1;
			cmd_ptr->fd_pipe_out = piped[1];
			if (!(ptr = ptr->next))
				break ;
			else
				continue;
		}
		if (ptr && !sep_checker(ptr->content))
			while(ptr && !sep_checker(ptr->content))
			{
				ft_lstadd_back(&cmd_ptr->str, ft_lstnew(ft_strdup(ptr->content)));
				if (!(ptr = ptr->next))
					break ;
			}
		else
			if (!(ptr = ptr->next) || !ft_strcmp(ptr->content, ";"))
				continue ;
		if (ptr && !ft_strcmp(ptr->content, "|"))
		{
			pipe(piped);
			cmd_ptr->pipe_out = 1;
			cmd_ptr->fd_pipe_out = piped[1];
			if (!(ptr = ptr->next))
				break ;
			else
				continue;
		}
		if (!ptr || !ft_strcmp(ptr->content, ";") || !(ptr = ptr->next))
			continue ;
	}
	return (0);
}

int			parser(t_sarg *t)
{
	char	*str;

	str = NULL;
	if (t->arg_lst)
		str = t->arg_lst->content;
	return (chain_maker(t));
}

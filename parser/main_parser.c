/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 01:53:26 by jsilance          #+#    #+#             */
/*   Updated: 2021/02/14 18:01:333 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cmd_flag_check(char *str)
{
	if (!ft_strncmp("-n", str, 2))
		return (1);
	return (0);
}

static int	cmd_checker(char *str)
{
	if (str)
	{
		if (!ft_strcmp("exit", str))
			return (EXIT);
		else if (!ft_strcmp("echo", str))
			return (ECHO);
		else if (!ft_strcmp("cd", str))
			return (CD);
		else if (!ft_strcmp("pwd", str))
			return (PWD);
		else if (!ft_strcmp("export", str))
			return (EXPORT);
		else if (!ft_strcmp("unset", str))
			return (UNSET);
		else if (!ft_strcmp("env", str))
			return (ENV);
	}
	// return (ft_error(1, -1));
	return (OTHER);
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
**	cmd_index -1 --> autre
**	cmd_index  0 --> exit
**	cmd_index  1 --> echo
**	cmd_index  2 --> cd
**	cmd_index  3 --> pwd
**	cmd_index  4 --> export
**	cmd_index  5 --> unset
**	cmd_index  6 --> env
*/

/*
static int	chain_maker(t_sh *t)
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
			cmd_checker(ptr->content)));
		cmd_ptr = ft_cmd_lstlast(t->cmd);
		cmd_ptr->cmd_str = ft_strdup(ptr->content);
		if (piped[0] > -1)
		{
			cmd_ptr->fd_pipe_in = piped[0];
			cmd_ptr->pipe_in = 1;
			piped[0] = -1;
		}
		if (!(ptr = ptr->next) || !ft_strcmp(ptr->content, ";"))
			continue ;
		while (ptr && cmd_ptr->cmd_index == 1 && cmd_flag_check(ptr->content))
		{
			free(cmd_ptr->flags);
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
		if (ptr && !ft_strcmp(ptr->content, ">>"))
		{
			cmd_ptr->pipe_out = 3;
			if (!(ptr = ptr->next))
				break ;
			while (ptr && !sep_checker(ptr->content))
			{
				ft_lstadd_back(&cmd_ptr->red_file, ft_lstnew(ft_strdup(ptr->content)));
				ptr = ptr->next;
			}
			continue;
		}
		if (ptr && !ft_strcmp(ptr->content, ">"))
		{
			cmd_ptr->pipe_out = 2;
			
			if (!(ptr = ptr->next))
				break ;
			while (ptr && !sep_checker(ptr->content))
			{
				ft_lstadd_back(&cmd_ptr->red_file, ft_lstnew(ft_strdup(ptr->content)));
				ptr = ptr->next;
			}
			continue;
		}
		if (ptr && !ft_strcmp(ptr->content, "<"))
		{
			cmd_ptr->pipe_out = 4;
			
			if (!(ptr = ptr->next))
				break ;
			while (ptr && !sep_checker(ptr->content))
			{
				ft_lstadd_back(&cmd_ptr->red_file, ft_lstnew(ft_strdup(ptr->content)));
				ptr = ptr->next;
			}
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
			if (!ptr || !(ptr = ptr->next) || !ft_strcmp(ptr->content, ";"))
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
		if (ptr && !ft_strcmp(ptr->content, ">>"))
		{
			cmd_ptr->pipe_out = 3;
			if (!(ptr = ptr->next))
				break ;
			while (ptr && !sep_checker(ptr->content))
			{
				ft_lstadd_back(&cmd_ptr->red_file, ft_lstnew(ft_strdup(ptr->content)));
				ptr = ptr->next;
			}
			continue;
		}
		if (ptr && !ft_strcmp(ptr->content, ">"))
		{
			cmd_ptr->pipe_out = 2;
			
			if (!(ptr = ptr->next))
				break ;
			while (ptr && !sep_checker(ptr->content))
			{
				ft_lstadd_back(&cmd_ptr->red_file, ft_lstnew(ft_strdup(ptr->content)));
				ptr = ptr->next;
			}
			continue;
		}
		if (ptr && !ft_strcmp(ptr->content, "<"))
		{
			cmd_ptr->pipe_out = 4;
			
			if (!(ptr = ptr->next))
				break ;
			while (ptr && !sep_checker(ptr->content))
			{
				ft_lstadd_back(&cmd_ptr->red_file, ft_lstnew(ft_strdup(ptr->content)));
				ptr = ptr->next;
			}
			continue;
		}
		if (!ptr || !ft_strcmp(ptr->content, ";") || !(ptr = ptr->next))
			continue ;
	}
	return (0);
}
*/

static void *new_cmd(t_sh *sh)
{
	ft_cmd_lstadd_back(&sh->cmd, ft_cmd_lstnew(NULL, NULL,
		cmd_checker(sh->parser.ptr_lst->content)));
	sh->parser.ptr_cmd = ft_cmd_lstlast(sh->cmd);
	sh->parser.ptr_cmd->cmd_str = ft_strdup(sh->parser.ptr_lst->content);
}

// ptr_lst == lst argument

static int set_pipe(t_sh *sh)
{
	pipe(sh->parser.ptr_lst);
	sh->parser.ptr_cmd->pipe_out = 1;
	sh->parser.ptr_cmd->fd_pipe_out = sh->parser.piped[1];
	if (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next))
		return (0);
	else
		return (1);
}

static int set_left_red(t_sh *sh)
{
	sh->parser.ptr_cmd->pipe_out = 4;
	if (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next))
		return (0) ;
	while (sh->parser.ptr_lst && !sep_checker(sh->parser.ptr_lst->content))
	{
		ft_lstadd_back(&sh->parser.ptr_cmd->red_file, ft_lstnew(ft_strdup(sh->parser.ptr_lst->content)));
		sh->parser.ptr_lst = sh->parser.ptr_lst->next;
	}
	return (1);
}

static int set_simple_red(t_sh *sh)
{
	if (sh->parser.ptr_lst && !ft_strcmp(sh->parser.ptr_lst->content, ">"))
	{
		sh->parser.ptr_cmd->pipe_out = 2;
		
		if (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next))
			return (0);
		while (sh->parser.ptr_lst && !sep_checker(sh->parser.ptr_lst->content))
		{
			ft_lstadd_back(&sh->parser.ptr_cmd->red_file, ft_lstnew(ft_strdup(sh->parser.ptr_lst->content)));
			sh->parser.ptr_lst = sh->parser.ptr_lst->next;
		}
		return (1);
	}
}

static int set_double_red(t_sh *sh)
{
	sh->parser.ptr_cmd->pipe_out = 3;
	if (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next))
		return (0);
	while (sh->parser.ptr_lst && !sep_checker(sh->parser.ptr_lst->content))
	{
		ft_lstadd_back(&sh->parser.ptr_cmd->red_file, ft_lstnew(ft_strdup(sh->parser.ptr_lst->content)));
		sh->parser.ptr_lst = sh->parser.ptr_lst->next;
	}
	return (1);
}

static int set_pipe_red(t_sh *sh)
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

static int parsing(t_sh *sh)
{
	int ret;

	new_cmd(sh);
	if (sh->parser.piped[0] > -1)
	{
		sh->parser.ptr_cmd->fd_pipe_in = sh->parser.piped[0];
		sh->parser.ptr_cmd->pipe_in = 1;
		sh->parser.piped[0] = -1;
	}
	if (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next) || !ft_strcmp(sh->parser.ptr_lst->content, ";"))
		return (1);
	while (sh->parser.ptr_lst && sh->parser.ptr_cmd->cmd_index == ECHO && cmd_flag_check(sh->parser.ptr_lst->content))
	{
		free(sh->parser.ptr_cmd->flags);
		sh->parser.ptr_cmd->flags = ft_strdup(sh->parser.ptr_lst->content);
		if (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next) || !ft_strcmp(sh->parser.ptr_lst->content, ";"))
			return (0);
	}
	if (ret = set_pipe_red < 0)
		return (ret);
	if (ptr && !sep_checker(ptr->content))
	{
		while(ptr && !sep_checker(ptr->content))
		{
			ft_lstadd_back(&cmd_ptr->str, ft_lstnew(ft_strdup(ptr->content)));
			if (!(ptr = ptr->next))
				break ;
		}
	}
	else
		if (!ptr || !(ptr = ptr->next) || !ft_strcmp(ptr->content, ";"))
			continue ;
}

pwd 
static void start_process(t_sh *sh)
{
	t_list		*ptr;

	sh->parser.ptr_lst = sh->arg_lst;
	while (sh->parser.ptr_lst)
	{
		if (!ft_strcmp(sh->parser.ptr_lst->content, ";") && (ft_print_error(SYNTAX_ERROR,
			';')))
			break ;
		if (parsing(sh))
			continue ;
		else
			return ;
	}
}

void			parser(t_sh *sh)
{
	char	*str;

	str = NULL;
	if (sh->arg_lst)
		str = sh->arg_lst->content;
	start_process(sh);
}

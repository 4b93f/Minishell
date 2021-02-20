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

int			sep_checker(char *str)
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

static void new_cmd(t_sh *sh)
{
	ft_cmd_lstadd_back(&sh->cmd, ft_cmd_lstnew(NULL, NULL,
		cmd_checker(sh->parser.ptr_lst->content)));
	sh->parser.ptr_cmd = ft_cmd_lstlast(sh->cmd);
	sh->parser.ptr_cmd->cmd_str = ft_strdup(sh->parser.ptr_lst->content);
	printf("|%s|\n", sh->parser.ptr_cmd->cmd_str);
	return ;
}

/*
**	ptr_lst == lst argument
*/

static void	backsl(t_list *ptr)
{
	char	*str;
	char	*tmp;

	if (!ptr)
		return ;
	str = (char *)ptr->content;
	if (str[0] == '\\' && !str[1])
	{
		free(ptr->content);
		ptr->content = ft_strdup(" ");
	}
	else if (str[0] == '\\' && str[1])
	{
		tmp = ft_strdup(ptr->content);
		free(ptr->content);
		ptr->content = ft_substr(tmp, 1, 1);
		free(tmp);
	}
}

int			lex_to_cmdstr(t_sh *sh)
{
	//printf("!\n");
	//printf("%s\n", sh->parser.ptr_lst->content);
	if (sh->parser.ptr_lst && !sep_checker(sh->parser.ptr_lst->content))
	{
		while(sh->parser.ptr_lst && !sep_checker(sh->parser.ptr_lst->content))
		{
			//backsl(sh->parser.ptr_lst); // temporaire a implementer dans le lexer
			ft_lstadd_back(&sh->parser.ptr_cmd->str, ft_lstnew(ft_strdup(sh->parser.ptr_lst->content)));
			if (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next))
				return (0);
		}
	}
	else
		if (!sh->parser.ptr_lst || !(sh->parser.ptr_lst = sh->parser.ptr_lst->next) || !ft_strcmp(sh->parser.ptr_lst->content, ";"))
			return (0);
	return (-1);
}

static int	parsing(t_sh *sh)
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
			return (1);
	}
	if (ret == (set_pipe_red(sh)) > -1)
		return (ret);
	if (ret == (lex_to_cmdstr(sh)) > -1)
		return (ret);
	if (ret == (set_pipe_red(sh)) > -1)
		return (ret);
// printf("***[%s]***\n", sh->parser.ptr_lst->content);

// *********|POSE PROBLEME AVEC LES PIPES|*********
	if (sh->parser.ptr_lst && (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next) || !ft_strcmp(sh->parser.ptr_lst->content, ";")))
		return (1);

	return (1);
}


static void start_process(t_sh *sh)
{
	sh->parser.ptr_lst = sh->arg_lst;
	if (!sh->parser.ptr_lst)
		return ;
	if (!ft_strcmp(sh->parser.ptr_lst->content, ";"))
	{
		printf("minishell: ");
		ft_print_error(SYNTAX_ERROR, sh->parser.ptr_lst->content);
		return ;
	}
	while (sh->parser.ptr_lst)
	{
		if (parsing(sh))
		{
			if(sh->parser.ptr_lst && !ft_strcmp(sh->parser.ptr_lst->content, ";"))
				sh->parser.ptr_lst = sh->parser.ptr_lst->next;
			continue ;
		}
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

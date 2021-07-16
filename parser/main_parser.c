/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 01:53:26 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/16 22:35:42 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	new_cmd(t_sh *sh)
{
	sh->parser.ptr_lst->content = rm_guim(sh->parser.ptr_lst->content);
	ft_cmd_lstadd_back(&sh->cmd, ft_cmd_lstnew(NULL, NULL,
			cmd_checker(sh->parser.ptr_lst->content)));
	sh->parser.ptr_cmd = ft_cmd_lstlast(sh->cmd);
	sh->parser.ptr_cmd->cmd_str = ft_strdup(sh->parser.ptr_lst->content);
	return ;
}

static int	parsing(t_sh *sh)
{
	int	ret;

	new_cmd(sh);
	if (sh->parser.piped[0] > -1)
	{
		sh->parser.ptr_cmd->fd_pipe_in = sh->parser.piped[0];
		sh->parser.ptr_cmd->pipe_in = 1;
		sh->parser.piped[0] = -1;
	}
	if (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next)
		|| !ft_strcmp(sh->parser.ptr_lst->content, ";"))
		return (1);
	while (sh->parser.ptr_lst && sh->parser.ptr_cmd->cmd_index == ECHO && cmd_flag_check(sh->parser.ptr_lst->content))
	{
		free(sh->parser.ptr_cmd->flags);
		sh->parser.ptr_cmd->flags = ft_strdup(sh->parser.ptr_lst->content);
		if (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next) || !ft_strcmp(sh->parser.ptr_lst->content, ";"))
			return (1);
	}
	ret = set_pipe_red(sh);
	if (ret > -1)
		return (ret);
	ret = lex_to_cmdstr(sh);
	if (ret > -1)
		return (ret);
	ret = set_pipe_red(sh);
	if (ret > -1)
		return (ret);
	if (sh->parser.ptr_lst && (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next) || !ft_strcmp(sh->parser.ptr_lst->content, ";")))
		return (1);
	return (1);
}

void	parser(t_sh *sh)
{
	char	*str;

	if (!sh->arg_lst)
		return ;
	sh->parser.ptr_lst = sh->arg_lst;
	if (!sh->parser.ptr_lst)
		return ;
	if (!ft_strcmp(sh->parser.ptr_lst->content, ";"))
	{
		printf("minishell: ");
		ft_print_error(SYNTAX_ERROR, sh->parser.ptr_lst->content);
		ft_set_free_env(sh, "?", ft_itoa(2));
		return ;
	}
	while (sh->parser.ptr_lst)
	{
		if (parsing(sh))
		{
			if (sh->parser.ptr_lst && !ft_strcmp(sh->parser.ptr_lst->content, ";"))
				sh->parser.ptr_lst = sh->parser.ptr_lst->next;
		}
		else if (!sh->parser.ptr_lst && sh->parser.ptr_cmd->pipe_out == PIPE)
		{
			str = NULL;
			write(1, "> ", 2);
			get_next_line(0, &str);
			if (str)
			{
				sh->input_str = ft_strjoinfree(sh->input_str, str);
				strtolst(sh);
			}
			free(str);
			parser(sh);
		}
		else
			return ;
	}
}

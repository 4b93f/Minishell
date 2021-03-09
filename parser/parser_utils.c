/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:56:35 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/08 22:15:58 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		sep_checker(char *str)
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

int		lex_to_cmdstr(t_sh *sh)
{
	if (sh->parser.ptr_lst && !sep_checker(sh->parser.ptr_lst->content))
	{
		while(sh->parser.ptr_lst && !sep_checker(sh->parser.ptr_lst->content))
		{
			ft_lstadd_back(&sh->parser.ptr_cmd->str, ft_lstnew(ft_strdup(sh->parser.ptr_lst->content)));
			if (!(sh->parser.ptr_lst = sh->parser.ptr_lst->next))
				return (0);
		}
	}
	else if (!sh->parser.ptr_lst || !(sh->parser.ptr_lst = sh->parser.ptr_lst->next) || !ft_strcmp(sh->parser.ptr_lst->content, ";"))
			return (0);
	return (-1);
}

int		cmd_checker(char *str)
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
	return (OTHER);
}

int		cmd_flag_check(char *str)
{
	if (!ft_strncmp("-n", str, 2))
		return (1);
	return (0);
}

void	backsl(t_list *ptr)
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

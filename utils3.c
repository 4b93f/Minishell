/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:49:55 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/10 17:50:31 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct/struct.h"

void	get_all_path(t_sh *sh)
{
	int			i;

	i = -1;
	sh->ptr_env = sh->lst_env;
	while (sh->ptr_env && ft_strcmp(sh->ptr_env->var, "PATH"))
		sh->ptr_env = sh->ptr_env->next;
	if (!sh->ptr_env)
		return ;
	sh->all_path = ft_split(sh->ptr_env->content, ':');
	if (!sh->all_path)
		return ;
	while (sh->all_path[++i])
	{
		sh->free_ptr = sh->all_path[i];
		sh->all_path[i] = ft_strjoin(sh->all_path[i], "/");
		free(sh->free_ptr);
	}
}

int	previous_type(t_sh *sh, t_lst_cmd *ptr)
{
	t_lst_cmd	*parse;

	parse = sh->lst_cmd;
	while (parse && parse->next != ptr)
		parse = parse->next;
	if (!parse)
		return (0);
	return (parse->type);
}

t_lst_cmd	*previous_sep(t_sh *sh, t_lst_cmd *ptr)
{
	t_lst_cmd	*parse;
	t_lst_cmd	*stock;

	if ((cmd_lstsize(ptr) - cmd_lstsize(sh->lst_cmd)) == 0)
		return (NULL);
	parse = sh->lst_cmd;
	stock = parse;
	while (parse)
	{
		stock = parse;
		parse = next_sep(parse);
		if (ptr == parse)
			return (stock);
		if (parse == NULL)
			return (stock);
	}
	return (NULL);
}

t_lst_cmd	*next_sep(t_lst_cmd *ptr)
{
	if (!ptr)
		return (NULL);
	while (ptr)
	{
		if (str_sep(ptr->cmd) && ptr->next)
			return (ptr->next);
		ptr = ptr->next;
	}
	return (NULL);
}

int	red_error(t_sh *sh)
{
	if (!sh->ptr_cmd)
	{
		ft_putstr_fd("My Minishell: syntax error near", 2);
		ft_putstr_fd("unexpected token`newline'", 2);
		return (1);
	}
	else if (str_spechar(sh->ptr_cmd->cmd))
	{
		errno = SYNTAX_ERROR;
		error(sh, sh->ptr_cmd->cmd);
		sh->block_cmd = 1;
		exit_code(sh, 0);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:24:54 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/10 19:27:08 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

t_lst_cmd	*next_sep2(t_lst_cmd *ptr)
{
	if (!ptr)
		return (NULL);
	while (ptr)
	{
		if (str_sep(ptr->cmd))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

int	index_token(t_sh *sh, t_lst_cmd *ptr)
{
	int			i;
	t_lst_cmd	*parse;

	i = 0;
	if (!ptr)
		return (-1);
	parse = sh->lst_cmd;
	while (parse)
	{
		if (parse == ptr)
			return (i);
		parse = parse->next;
		i++;
	}
	return (i);
}

int	get_redir_number(t_sh *sh)
{
	int	i;

	i = 0;
	sh->ptr_cmd = sh->lst_cmd;
	while (sh->ptr_cmd)
	{
		if (sh->ptr_cmd->redirected == 1)
			i++;
		sh->ptr_cmd = sh->ptr_cmd->next;
	}
	return (i);
}

void	go_end(t_sh *sh, t_lst_cmd *token)
{
	t_lst_cmd	*last;
	t_lst_cmd	*stock;

	(void)last;
	stock = sh->lst_cmd;
	cmd_lstaddback(&sh->lst_cmd,
		cmd_lstnew(ft_strdup(token->cmd), token->type, token->redirected));
	token->type = -1;
}

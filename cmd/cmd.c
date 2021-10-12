/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:21:23 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/10 19:26:52 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

t_lst_cmd	*prev_token(t_sh *sh, t_lst_cmd *ptr)
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
		parse = parse->next;
		if (ptr == parse)
			return (stock);
		if (parse == NULL)
			return (stock);
	}
	return (NULL);
}

t_lst_cmd	*next_token(t_lst_cmd *ptr)
{
	if (!ptr)
		return (NULL);
	return (ptr->next);
}

t_lst_cmd	*new_lst(t_sh *sh)
{
	t_lst_cmd	*new_lst;
	t_lst_cmd	*ptr_cmd;

	new_lst = NULL;
	ptr_cmd = sh->lst_cmd;
	while (ptr_cmd)
	{
		if (ptr_cmd->type != -1)
			cmd_lstaddback(&new_lst,
				cmd_lstnew(ft_strdup(ptr_cmd->cmd), ptr_cmd->type, ptr_cmd->redirected));
		ptr_cmd = ptr_cmd->next;
	}
	return (new_lst);
}

void	type(t_lst_cmd *cmd, t_lst_cmd *prev)
{	
	if (prev)
		if (prev->type == RIGHT || prev->type == LEFT
			|| prev->type == DRIGHT || prev->type == DLEFT)
			cmd->redirected = 1;
	if (cmd->type)
		(void)NULL;
	else if (!prev || (prev->type != ARG && prev->type != CMD))
		cmd->type = CMD;
	else
		cmd->type = ARG;
}

void	get_type(t_sh *sh)
{
	t_lst_cmd	*prev;

	sh->ptr_cmd = sh->lst_cmd;
	while (sh->ptr_cmd)
	{
		prev = prev_token(sh, sh->ptr_cmd);
		if (!sh->ptr_cmd->type)
			type(sh->ptr_cmd, prev);
		sh->ptr_cmd = sh->ptr_cmd->next;
	}
}

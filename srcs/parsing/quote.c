/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:05:20 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/10 16:43:19 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void	is_quote_open(char *str, int *squote, int *dquote, int i)
{
	if (!str)
		return ;
	if (*squote == 1 && str[i] == '\'')
		*squote = FALSE;
	else if (*squote == 0 && str[i] == '\'')
		*squote = TRUE;
	if (*dquote == 1 && str[i] == '\"')
		*dquote = FALSE;
	else if (*dquote == 0 && str[i] == '\"')
		*dquote = TRUE;
}

void	dquoting(t_sh *sh, int *i, int *j)
{
	if (sh->ptr_cmd->cmd[*i + 1] != '\"')
	{
		while (sh->ptr_cmd->cmd[*i] && sh->ptr_cmd->cmd[*i + 1] != '\"')
		{
			sh->ptr_cmd->cmd[*j] = sh->ptr_cmd->cmd[*i + 1];
			*j = *j + 1;
			*i = *i + 1;
		}
	}
}

void	squoting(t_sh *sh, int *i, int *j)
{
	if (sh->ptr_cmd->cmd[*i + 1] != '\'')
	{
		while (sh->ptr_cmd->cmd[*i] && sh->ptr_cmd->cmd[*i + 1] != '\'')
		{
			sh->ptr_cmd->cmd[*j] = sh->ptr_cmd->cmd[*i + 1];
			*j = *j + 1;
			*i = *i + 1;
		}
	}
}

void	quoting(t_sh *sh)
{
	int	i;
	int	j;

	sh->ptr_cmd = sh->lst_cmd;
	while (sh->ptr_cmd)
	{
		i = 0;
		j = 0;
		while (sh->ptr_cmd->cmd[i])
		{
			if (sh->ptr_cmd->cmd[i] == '\"')
				dquoting(sh, &i, &j);
			else if (sh->ptr_cmd->cmd[i] == '\'')
				squoting(sh, &i, &j);
			else
				j++;
			i++;
		}
		sh->ptr_cmd = sh->ptr_cmd->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:46:21 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/15 16:19:04 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	if double ; return error and no commands executed.
**	suppression du &.
*/

static void	str_cut(t_sh *t, int i, int j)
{
	while (t->input_str && t->input_str[i])
	{
		if (t->input_str[i] && t->input_str[i] == '\"')
		{
			i++;
			while (t->input_str[i] && t->input_str[i] != '\"')
				if (t->input_str[i++] == '\\')
					i++;
			i++;
			continue ;
		}
		if (t->input_str[i] && t->input_str[i] == '\'')
		{
			i++;
			while (t->input_str[i] && t->input_str[i] != '\'')
				if (t->input_str[i++] == '\\')
					i++;
			i++;
			continue ;
		}
		if ((ft_strchr(" ><|;", t->input_str[i]) && t->input_str[i - 1] != '\\'))
		{
			if (is_double_char(t, i))
				str_store(t, j, i++, 2);
			else
				str_store(t, j, i, 1);
			j = i + 1;
		}
		i++;
	}
	if (!t->input_str[i])
		str_store(t, j, i, 0);
}

void	strtolst(t_sh *t)
{
	str_cut(t, 0, 0);
}

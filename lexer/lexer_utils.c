/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:46:08 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/14 18:47:46 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*quoting(char *str)
{
	char	*new_str;
	int		i;
	int		j;


	new_str = ft_calloc(1, ft_strlen(str));
	i = 0;
	j = 0;
	if (!str || !new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				if (str[i] == '\\')
					new_str[j++] = str[i++];
				new_str[j++] = str[i++];
			}
			i++;
			new_str[j] = 0;
			continue ;
		}
		if (str[i] && str[i] == '\"')
		{
			i++;
			if (str[i - 1] == '\\')
				new_str[j++] = str[i++];
			while (str[i] && str[i] != '\"')
			{
				if (str[i] == '\\')
					new_str[j++] = str[i++];
				new_str[j++] = str[i++];
			}
			i++;
			new_str[j] = 0;
			continue ;
		}
		new_str[j++] = str[i++];
		new_str[j] = 0;
	}
	free(str);
	return (new_str);
}

void	str_store(t_sh *t, int j, int i, int sep)
{
	if (i - j > 0)
		ft_lstadd_back(&t->arg_lst, ft_lstnew(quoting(ft_substr(t->input_str, j,
			i - j))));
	if (sep && t->input_str[i] && ft_strchr("<>|;", t->input_str[i]))
		ft_lstadd_back(&t->arg_lst, ft_lstnew(quoting(ft_substr(t->input_str,
			i, sep))));
}

int		is_double_char(t_sh *t, int i)
{
	return ((t->input_str[i] == '>' && t->input_str[i + 1] == '>') ||
		(t->input_str[i] == '<' && t->input_str[i + 1] == '<') ||
		(t->input_str[i] == '|' && t->input_str[i + 1] == '|') ||
		(t->input_str[i] == '&' && t->input_str[i + 1] == '&'));
}
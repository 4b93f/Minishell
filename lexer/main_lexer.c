/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:46:21 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/02 16:40:24 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	need to trim when " or ' is used.
*/

static void	str_store(t_sh *t, int j, int i, int sep)
{
	if (i - j > 0)
		ft_lstadd_back(&t->arg_lst, ft_lstnew(ft_substr(t->input_str, j,
			i - j)));
	if (sep && t->input_str[i] && ft_strchr("<>|;", t->input_str[i]))
		ft_lstadd_back(&t->arg_lst, ft_lstnew(ft_substr(t->input_str,
			i, sep)));
}

static int	is_double_char(t_sh *t, int i)
{
	return ((t->input_str[i] == '>' && t->input_str[i + 1] == '>') ||
		(t->input_str[i] == '<' && t->input_str[i + 1] == '<') ||
		(t->input_str[i] == '|' && t->input_str[i + 1] == '|') ||
		(t->input_str[i] == '&' && t->input_str[i + 1] == '&'));
}

/*
**	if double ; return error and no commands executed.
**	suppression du &.
*/

static void	str_cut(t_sh *t, int i, int j)
{
	while (t->input_str && t->input_str[i])
	{
		if ((ft_strchr(" ><|;", t->input_str[i]) || ft_isspace(t->input_str[i])) && t->input_str[i - 1] != '\\')
		{
			if (is_double_char(t, i))
				str_store(t, j, i++, 2);
			else
				str_store(t, j, i, 1);
			j = i + 1;
		}
		else if (t->input_str[i] == '"' || t->input_str[i] == '\'')
		{
			i++;
			while (t->input_str[i] && !ft_strchr("\"'", t->input_str[i]))
				i++;
			str_store(t, j, i + 1, 1);
			j = i + 1;
		}
		i++;
	}
	if (!t->input_str[i])
		str_store(t, j, i, 0);
}

static char *del_quote(char *str)
{
	char *dup;
	int i;
	int j;

	i = -1;
	j = 0;
	dup = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	while (str[++i])
	{
		while (str[i] == '\'' || str[i] == '\"')
			i++;	
		dup[j] = str[i];
		j++;
	}
	dup[j] = '\0';
	free(str);
	return(dup);
}

void		strtolst(t_sh *t)
{
	//t->input_str = del_quote(t->input_str);
	str_cut(t, 0, 0);
	//printf("<%s>\n", t->input_str);
}

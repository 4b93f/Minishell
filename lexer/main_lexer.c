/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:46:21 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/10 21:15:23 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	need to trim when " or ' is used.
*/

static void	str_store(t_sh *t, int j, int i, int sep)
{
	// write(1, "***", 3);
	// write(1, &t->input_str[j], i - j);
	// write(1, "***\n", 4);
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
		if ((t->input_str[i] == '\"' || t->input_str[i] == '\'') && t->input_str[i - 1] != '\\' && (ft_strchr(" ><|;", t->input_str[i - 1])))
		{
			i++;
			while (t->input_str[i] && (!ft_strchr("\"\'", t->input_str[i]) || ft_strchr(" ><|;", t->input_str[i]) || ft_isspace(t->input_str[i])))
				i++;
			if (!((ft_strchr(" ><|;", t->input_str[i]) || ft_isspace(t->input_str[i])) && t->input_str[i - 1] != '\\'))
				continue ;
			str_store(t, j, i + 1, 1);
			j = i + 1;
		}
		else if ((ft_strchr(" ><|;", t->input_str[i]) && t->input_str[i - 1] != '\\'))
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

static int		word_count(char *str, char *strset)
{
	int	i;
	int len;

	i = 0;
	len = 0;
	while (str[i])
	{
		while (str[i] && (ft_strchr(strset, str[i])))
			i++;
		if (str[i++] && (!ft_strchr(strset, str[i])))
			while (str[i] && (!ft_strchr(strset, str[i])))
				i++;
		len++;
		while (str[i] && (ft_strchr(strset, str[i])))
			i++;
	}
	return (len);
}

char **stock(t_sh *sh)
{
	char **str;
	int len;
	int i;
	int j;

	len = word_count(sh->input_str, " \"\'><|;");
	str = malloc(sizeof(char *) * (len + 1));
	
	len = 0;
	i = -1;
	while (sh->input_str[++i])
	{
		str[len] = malloc(sizeof(char) * (ft_strlen(sh->input_str) + 1));
		j = -1;
		while (sh->input_str[i] && (ft_strchr(" \"\'><|;", sh->input_str[i])))
			i++;
		if (sh->input_str[i] && (!ft_strchr(" \"\'><|;", sh->input_str[i])))
			while (sh->input_str[i] && (!ft_strchr(" \"\'><|;", sh->input_str[i])))
				str[len][++j] = sh->input_str[i++];
		// if (sh->input_str[i] && (ft_strchr(" ", sh->input_str[i])))
		// 	while (sh->input_str[i] && (ft_strchr(" ", sh->input_str[i])))
		// 		str[len][++j] = sh->input_str[i++];
		str[len][++j] = '\0';
		len++;
	}
	return (str);
}
void		strtolst(t_sh *t)
{
	str_cut(t, 0, 0);
	t->stock = stock(t);
}

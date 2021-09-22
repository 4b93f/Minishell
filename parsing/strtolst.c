/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtolst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:31:11 by chly-huc          #+#    #+#             */
/*   Updated: 2021/09/22 20:23:46 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

char *ft_remove_char(char *str, int c)
{
	int i;
	int j;
	char *dup;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	dup = malloc(sizeof(char * ) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			dup[j] = str[i];
		i++;
		j++;
	}
	dup[j + 1] = '\0';
	return (dup);
	
}

int ver_quote(char *str)
{
	int i;
	int dquote;
	int squote;

	i = 0;
	squote = 0;
	dquote = 0;
	if (!str)
		return(1);
	while (str[i])
	{
		is_quote_open(str, &squote, &dquote, i);
		i++;
	}
	if (squote || dquote)
	{
		printf("Error, unclose quote detected\n");
		return(0);
	}
	return(1);
}

void str_tolst(char *str, t_sh *sh)
{
	int i;
	int j;
	int dquote;
	int squote;
	int type;
	char *tmp;
	
	j = 0;
	i = 0;
	tmp = str;
	squote = 0;
	dquote = 0;
	while (tmp[i])
	{
		j = i;
		type = 0;
		if (tmp[i] && !is_sep(tmp[i]))
		{
			while (tmp[i] && (!is_sep(tmp[i]) || squote || dquote))
			{
				is_quote_open(tmp, &squote, &dquote, i);
				i++;
			}
		}
		else if (tmp[i] == ' ')
		{
			i++;
			continue;
		}
		else
		{
			i++;
			if (str[i - 1] == '|')
				type = PIPE;
			if (str[i - 1] == '>')
				type = RIGHT;
			else if (str[i - 1] == str[i] && str[i - 1] == '>')
				type = DRIGHT;
			else if (str[i - 1]  == '<')
				type = LEFT;
			else if (str[i - 1] == str[i] && str[i - 1] == '<')
				type = DLEFT;
			while(str[i - 1] == str[i] && is_sep(str[i]))
				i++;
		}
		cmd_lstaddback(&sh->lst_cmd, cmd_lstnew(ft_substr(tmp, j, i - j), type));
	}
	return ;
}
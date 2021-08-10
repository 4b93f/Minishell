/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:05:20 by chly-huc          #+#    #+#             */
/*   Updated: 2021/08/10 22:15:58 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void is_quote_open(char *str, int *squote, int *dquote, int i)
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

void dquoting(t_sh *sh, char *str, int *i, int *j)
{
	if (str[*i + 1] != '\"')
	{
		while (str[*i] && str[*i + 1] && str[*i + 1] != '\"')
		{
			sh->dup[*j] = str[*i + 1];
			*j = *j + 1;
			*i = *i + 1;
		}
	}
	else
		while(str[*i + 1] == '\"')
			*i = *i + 1;
}

void squoting(t_sh *sh, char *str, int *i, int *j)
{
	if (str[*i + 1] != '\'')
	{
		while (str[*i] && str[*i + 1] && str[*i + 1] != '\'')
		{
			sh->dup[*j] = str[*i + 1];
			*j = *j + 1;
			*i = *i + 1;
		}
	}
	else
		while(str[*i + 1] == '\'')
			*i = *i + 1;
}

void quoting(t_sh *sh, char *str)
{
	int i = 0;
	int j = 0;

	sh->dup = malloc(sizeof(char*) * strlen(str) + 1);
	if (!sh->dup)
		return;
	while (str[i])
	{
		if (str[i] == '\"')
			dquoting(sh, str, &i, &j);
		else if (str[i] == '\'')
			squoting(sh, str, &i, &j);	
		else
		{
			sh->dup[j] = str[i];
			j++;
		}
		i++;
	}
	sh->dup[i] = '\0';
}

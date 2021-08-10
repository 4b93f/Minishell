/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:59:01 by chly-huc          #+#    #+#             */
/*   Updated: 2021/08/09 23:16:31 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void is_quote_open(char *str, int *squote, int *dquote, int i)
{
	if (!str)
		return ;
	if (*squote == 1 && str[i] == '\'')
	{
		if (*dquote == 1)
			dquote = 0;
		*squote = 0;
	}
	else if (*squote == 0 && str[i] == '\'')
		*squote = 1;
	if (*dquote == 1 && str[i] == '\"')
	{
		if (*squote == 1)
			squote = 0;
		*dquote = 0;
	}
	else if (*dquote == 0 && str[i] == '\"')
		*dquote = 1;
}

int main(int argc, char **argv)
{
	char *dup;
	char *str = strdup("lol\"\"\'\'\"");
	int i = 0;
	int j = 0;
	int squote = 0;
	int dquote = 0;

	printf("[%s]\n", str);
	dup = malloc(sizeof(char*) * strlen(str));
	while (str && str[j])
	{
		if (str[j + 1] && str[j] == '\'' && str[j + 1] != '\'')
			is_quote_open(str, &squote, &dquote, j);
		if (str[j + 1] && str[j] == '\"' && str[j + 1] != '\"')
			is_quote_open(str, &squote, &dquote, j);
		if (squote || dquote)
		{
			if (str[j] == '\"')
			{
				j++;
				while (str[j] && str[j] == '\"')
					j++;
				while (str[j] && str[j] != '\"')
				{
					dup[i] = str[j];
					i++;
					j++;
				}
			}
			if (str[j] == '\'')
			{
				j++;
				while (str[j] && str[j] == '\'')
					j++;
				while (str[j] && str[j] != '\'')
				{
					dup[i] = str[j];
					i++;
					j++;
				}
			}
		}
		else
		{
			if (str[j + 1])
				dup[i] = str[j];
			i++;
			j++;
		}
	}
	dup[i] = '\0';
	//printf("<%s>\n", dup);
}
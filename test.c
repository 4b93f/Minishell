/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:59:01 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/08 04:38:40 by chly-huc         ###   ########.fr       */
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
		*squote = 0;
	else if (*squote == 0 && str[i] == '\'')
		*squote = 1;
	if (*dquote == 1 && str[i] == '\"')
		*dquote = 0;
	else if (*dquote == 0 && str[i] == '\"')
		*dquote = 1;
}

void dquoting(char *str, char **dup, int *i, int *j)
{
	int x = j;
	if (str[*i + 1] != '\"')
	{
		while (str[*i] && str[*i + 1] && str[*i + 1] != '\"')
		{
			*dup[*j] = str[*i + 1];
			*j = *j + 1;
			*i = *i + 1;
		}
	}
	else
		while(str[*i + 1] == '\"')
			*i = *i + 1;
}

void squoting(char *str, char **dup, int *i, int *j)
{
	if (str[*i + 1] != '\'')
	{
		while (str[*i] && str[*i + 1] && str[*i + 1] != '\'')
		{
			*dup[*j] = str[*i + 1];
			*j = *j + 1;
			*i = *i + 1;
		}
	}
	else
		while(str[*i + 1] == '\'')
			*i = *i + 1;
}

char *adapt(char *str)
{
	char *dup;
	int i = 0;
	int j = 0;

	//lol"""''"""
	dup = malloc(sizeof(char*) * strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '\"')
		{
			if (str[i + 1] != '\"')
			{
				while (str[i] && str[i + 1] && str[i + 1] != '\"')
				{
					dup[j] = str[i + 1];
					j++;
					i++;
				}
			}
			else
			{
				while(str[i + 1] == '\"')
					i++;
				
			}
		}
		else if (str[i] == '\'')
		{
			if (str[i + 1] != '\'')
			{
				while (str[i] && str[i + 1] && str[i + 1] != '\'')
				{
					dup[j] = str[i + 1];
					j++;
					i++;
				}
			}
			else
			{
				while(str[i + 1] == '\'')
					i++;
				
			}
		}
		else
		{

			dup[j] = str[i];
			j++;
		}
		i++;
	}
	dup[i] = '\0';
	return(dup);
}

int main()
{
	char *str;

	str = strdup("echo \"\'\"");
	adapt(str);
}
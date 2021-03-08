/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:33:45 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/08 13:16:04 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include "executor.h"

char *fulltrim(char *s1, int c)
{
	char *dup;
	int i;
	int j;
	int first;

	dup = NULL;
	i = -1;
	j = -1;
	dup = malloc(sizeof(char*) * strlen(s1));
	if (!dup)
		return (NULL);
	while (s1[++i])
	{
		first = 0;
		while (s1[i] == c && ++first > 0)
			i++;
		if (first > 0)
			dup[++j] = c;
		dup[++j] = s1[i];
	}
	dup[++j] = '\0';
	free(s1);
	return (dup);
}


char *ft_backslash(char *s1)
{
	int i;
	int j;
	char *s2;

	i = -1;
	j = 0;
	if (!s1)
		return (NULL);
	s2 = malloc(sizeof(char*) * strlen(s1));
	if (!s2)
		return (NULL);
	while (s1[++i])
	{
		if (s1[i] == '\\')
			i++;
		if (s1[i])
			s2[j] = s1[i];
		j++;
	}
	s2[j] = 0;
	free(s1);
	return (s2);
}

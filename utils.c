/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:15:01 by chly-huc          #+#    #+#             */
/*   Updated: 2020/12/07 16:22:21 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int tablen(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		i++;
	return (i);	
}

void free_tab(char **tab)
{
	int i;

	i = -1;
	while(tab[++i])
		free(tab[i]);
	free(tab);
}

char **tabcpy(char **tab)
{
	char **new_tab;
	
	int i;
	new_tab = NULL;
	new_tab = (char**)malloc(sizeof(char*) * (tablen(tab) + 1));
	i = -1;
	while(tab[++i])
		new_tab[i] = ft_strdup(tab[i]);
	new_tab[i] = NULL;
	return(new_tab);
}

char	*ft_strjoinfree(const char *s1, const char *s2)
{
	char	*tab;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1)
		return (ft_strdup(s2));
	if (!(tab = malloc(sizeof(char) * ft_strlen((char*)s1)
					+ ft_strlen((char*)s2) + 1)))
		return (NULL);
	while (s1[++i])
		tab[i] = s1[i];
	while (s2[++j])
		tab[j + i] = s2[j];
	tab[i + j] = '\0';
	free((char*)s1);
	return (tab);
}

char	**ft_realloc(char **str, char *line)
{
	char	**cpy;
	int		i;

	cpy = NULL;
	i = 0;
	while (str[i] != NULL)
		i++;
	if (!(cpy = malloc(sizeof(char *) * (i + 2))))
		return(NULL);
	i = 0;
	while (str[i] != NULL)
	{
		cpy[i] = ft_strdup(str[i]);
		free(str[i]);
		i++;
	}
	cpy[i] = ft_strdup(line);
	cpy[i + 1] = NULL;
	free(str);
	return (cpy);
}

void print_tab(char **str)
{
	int i;

	i = -1;
	while(str[++i])
		printf("{%s}\n", str[i]);
	return ;
}

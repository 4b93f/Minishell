/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 02:10:35 by chly-huc          #+#    #+#             */
/*   Updated: 2021/04/23 17:42:04 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**malloc_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

static int	count_words(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == c))
			i++;
		if (str[i] && str[i] != c)
		{
			i++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (i);
}

static char	*malloc_word(char *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, char charset)
{
	int			words;
	static int	i = 0;
	char		**tab;

	if (!str)
		return (NULL);
	words = count_words(str, charset);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	while (*str)
	{
		while (*str && (*str == charset))
			str++;
		if (*str && *str != charset)
		{
			tab[i++] = malloc_word(str, charset);
			if (!tab[i])
				return (malloc_free(tab));
			while (*str && *str != charset)
				str++;
		}
	}
	tab[i] = NULL;
	return (tab);
}

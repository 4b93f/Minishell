/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtolst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:31:11 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/23 17:18:45 by chly-huc         ###   ########.fr       */
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

void str_tolst(char *str, t_sh *sh)
{
	int i;
	int j;
	char *tmp;
	

	j = 0;
	i = 0;
	tmp = str;
	while (tmp[i])
	{
		j = i;
		if (tmp[i] && !is_sep(tmp[i]))
			while (tmp[i] && !is_sep(tmp[i]))
				i++;
		else if (tmp[i] == ' ')
		{
			i++;
			continue;
		}
		else
			i++;
		cmd_lstaddback(&sh->lst_cmd, cmd_lstnew(ft_substr(tmp, j, i - j)));
	}
	return ;
}
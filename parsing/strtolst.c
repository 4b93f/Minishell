/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtolst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:31:11 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/12 22:19:28 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"


char *str_to_lst(char *str, t_sh *sh)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(str[j] && (str[j] == ' '))
		j++;
	i = j;
	if (str[i] == '|')
		while(str[i] == '|')
			i++;
	else
	{
		while(str[i] && str[i] != ' ')
		{
			i++;
			if (str[i] == '|')
				break;
		}
	}
	cmd_lstaddback(&sh->cmd, cmd_lstnew(ft_substr(str, j, i - j)));
	return (str + i);
}
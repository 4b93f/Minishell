/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 13:25:17 by chly-huc          #+#    #+#             */
/*   Updated: 2020/12/08 18:50:55 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void ft_search_path(t_sh *sh)
{
	struct stat buffer;
	char *tmp;
	int i;

	i = -1;
	while(sh->env[++i])
	{
		tmp = ft_strjoin(sh->env[i], sh->built_in);
		if (stat(tmp, &buffer))
		{
			free(tmp);
			return ;
		}
	}
	return ;
}
*/

void	get_all_path(t_sh *sh)
{
	int i;
	char *tmp;

	i = 0;
	while(strncmp(sh->env[i], "PATH=", ft_strlen("PATH=")))
		i++;
	if(!sh->env[i])
		return ;
	tmp = sh->env[i] + ft_strlen("PATH=");
	sh->all_path = ft_split(tmp, ':');
	i = -1;
	while (sh->all_path[++i])
		sh->all_path[i] = ft_strjoinfree(sh->all_path[i], "/");
	i = -1;
}


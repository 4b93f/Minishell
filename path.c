/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 13:25:17 by chly-huc          #+#    #+#             */
/*   Updated: 2021/01/24 23:46:20 by jsilance         ###   ########.fr       */
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
	int			i;
	char		*tmp;
	t_env_lst	*lst_ptr;

	i = -1;
	lst_ptr = sh->env_lst;
	while(ft_strcmp(lst_ptr->var, "PATH"))
		lst_ptr = lst_ptr->next;
	if(!lst_ptr)
		return ;
	sh->all_path = ft_split(lst_ptr->content, ':');
	while (sh->all_path[++i])
		sh->all_path[i] = ft_strjoinfree(sh->all_path[i], "/");
}


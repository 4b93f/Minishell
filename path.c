/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 13:25:17 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/03 01:50:32 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Return good path for the current command.
**	if the 
*/

char	*ft_search_path(t_sh *sh, t_cmd_lst *cmd)
{
	struct stat buffer;
	char *tmp;
	int i;

	i = -1;
	while(sh->all_path[++i])
	{
		tmp = ft_strjoin(sh->all_path[i], cmd->cmd_str);
		if (!tmp)
			ft_error(MALLOC_ERROR, sh, 0);
		if (!stat(tmp, &buffer))
		{
			free(tmp);
			return (sh->all_path[i]);
		}
		free(tmp);
	}
	return (NULL);
}

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
	sh->all_path = ft_split(lst_ptr->content, ':')
	if (!sh->all_path)
		return ;
	while (sh->all_path[++i])
		sh->all_path[i] = ft_strjoinfree(sh->all_path[i], "/");
}

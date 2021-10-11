/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:55:46 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/11 16:51:23 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

t_lst_env	*env_lstfinder(t_lst_env *lst, char *var)
{
	t_lst_env	*ptr_lst;

	ptr_lst = lst;
	if (!ptr_lst || !var)
		return (NULL);
	while (ptr_lst)
	{
		if (ptr_lst->var && !ft_strcmp(ptr_lst->var, var))
			return (ptr_lst);
		ptr_lst = ptr_lst->next;
	}
	return (NULL);
}

void	env_lstedit(t_sh *sh, char *var, char *value)
{
	sh->ptr_env = sh->lst_env;
	while (sh->ptr_env)
	{
		if (!ft_strcmp(sh->ptr_env->var, var))
		{
			free(sh->ptr_env->content);
			sh->ptr_env->content = ft_strdup(value);
		}
		sh->ptr_env = sh->ptr_env->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 16:04:46 by shyrno            #+#    #+#             */
/*   Updated: 2021/10/11 22:35:51 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

char	*env_lstcontent(t_sh *sh, char *str)
{
	t_lst_env	*ptr_lst;

	ptr_lst = sh->lst_env;
	if (!ptr_lst || !str)
		return (NULL);
	while (ptr_lst)
	{
		if (ptr_lst->var && !ft_strcmp(ptr_lst->var, str))
			return ((char *)ptr_lst->content);
		ptr_lst = ptr_lst->next;
	}
	return (NULL);
}

static int	init_var(int *equal_pos, char **var, int i, char **env)
{
	*equal_pos = ft_strchr(env[i], '=') - env[i];
	*var = ft_substr(env[i], 0, *equal_pos);
	if (!var)
		return (0);
	return (1);
}

void	env_tolst(char **env, t_sh *sh, int i, int equal_pos)
{
	char		*var;
	char		*value;
	t_lst_env	*new;

	while (env && env[++i])
	{
		if (!init_var(&equal_pos, &var, i, env))
			return ;
		value = ft_substr(env[i], equal_pos + 1, ft_strlen(env[i]));
		if (var && value)
			new = env_lstnew(var, value);
		if (new)
			env_lstaddback(&sh->lst_env, new);
		free(value);
		free(var);
	}
}

int	env_lstdupe(t_sh *sh, char *var, char *value)
{
	sh->ptr_env = sh->lst_env;
	while (sh->ptr_env)
	{
		if (!ft_strcmp(sh->ptr_env->var, var))
		{
			env_lstedit(sh, var, value);
			return (1);
		}
		sh->ptr_env = sh->ptr_env->next;
	}
	return (0);
}

void	env_lstdel(t_sh *sh, char *str)
{
	t_lst_env	*tmp;

	sh->ptr_env = sh->lst_env;
	if (sh->ptr_env && !sh->ptr_env->next)
		env_lstdelone(sh->ptr_env, free);
	while (sh->ptr_env && sh->ptr_env->next)
	{
		if (!ft_strcmp(((t_lst_env *)sh->ptr_env->next)->var, str))
		{
			tmp = ((t_lst_env *)sh->ptr_env->next)->next;
			env_lstdelone(sh->ptr_env->next, free);
			sh->ptr_env->next = tmp;
		}
		sh->ptr_env = sh->ptr_env->next;
	}
}

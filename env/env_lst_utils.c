/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 16:04:46 by shyrno            #+#    #+#             */
/*   Updated: 2021/07/25 00:20:27 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

// void	print_env(t_env_lst *lst, int fd, t_sh *sh)
// {
// 	t_env_lst	*ptr_lst;

// 	ptr_lst = lst;
// 	while (ptr_lst)
// 	{
// 		if (ptr_lst->var && ft_strcmp(ptr_lst->var, "?"))
// 		{
// 			ft_putstr_fd(ptr_lst->var, fd);
// 			write(fd, "=", 1);
// 			ft_putstr_fd(ptr_lst->content, fd);
// 			write(fd, "\n", 1);
// 		}
// 		ptr_lst = ptr_lst->next;
// 	}
// 	free(env_lst_finder(sh->env_lst, "?")->content);
// 	env_lst_finder(sh->env_lst, "?")->content = ft_itoa(0);
// }

char *env_lstcontent(t_sh *sh, char *str)
{
	t_lst_env	*ptr_lst;

	ptr_lst = sh->lst_env;
	if (!ptr_lst || !str)
		return (NULL);
	while (ptr_lst)
	{
		if (ptr_lst->var && !ft_strcmp(ptr_lst->var, str))
			return (ptr_lst->content);
		ptr_lst = ptr_lst->next;
	}
	return (NULL);
}

t_lst_env	*env_lstfinder(t_lst_env *lst, char *var)
{
	t_lst_env	*ptr_lst;
	t_lst_env	*tmp;

	tmp = NULL;
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
			sh->ptr_env->content = value;	
		sh->ptr_env = sh->ptr_env->next;
	}
}


void	env_tolst(char **env, t_sh *sh)
{
	int			i;
	int			equal_pos;
	char		*var;
	char		*value;
    t_lst_env	*new;

	sh->ptr_env = sh->lst_env;
	i = -1;
	while (env && env[++i])
	{
		equal_pos = ft_strchr(env[i], '=') - env[i];
		var = ft_substr(env[i], 0, equal_pos);
		if (!var)
			return ;
		value = ft_substr(env[i], equal_pos + 1, ft_strlen(env[i]));
		if (!value)
		{
			free(var);
			return ;
		}
		new = env_lstnew(var, value);
		if (!new)
		{
			free(var);
			free(value);
			return ;
		}
		env_lstaddback(&sh->lst_env, new);
	}
}

int env_lstdupe(t_sh *sh, char *var, char *value)
{
	sh->ptr_env = sh->lst_env;
	while (sh->ptr_env)
	{
		//printf("{%s} et {%s}\n", sh->ptr_env->content, value);
		if (!ft_strcmp(sh->ptr_env->var, var))
		{
			if (ft_strcmp(sh->ptr_env->content, value))
				env_lstedit(sh, var, value);
			return (1);
		}
		sh->ptr_env = sh->ptr_env->next;
	}
	return (0);
}

void env_lstdel(t_sh *sh, t_lst_env *delcontent)
{
	sh->ptr_env = sh->lst_env;
	t_lst_env *tmp;
	
	if (sh->ptr_env && !sh->ptr_env->next)
		env_lstdelone(sh->ptr_env, free);
	while(sh->ptr_env &&sh->ptr_env->next)
	{
		
		if (!ft_strcmp(((t_lst_env*)sh->ptr_env->next)->var, delcontent->var))
		{
			tmp = ((t_lst_env*)sh->ptr_env->next)->next;
			env_lstdelone(sh->ptr_env->next, free);
			sh->ptr_env->next = tmp;
		}
		sh->ptr_env = sh->ptr_env->next;
	}
}
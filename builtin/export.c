/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 14:26:34 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/25 00:13:53 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void print_export(t_sh *sh, char **tab)
{
	int i;

	i = 0;
	sh->ptr_env = sh->lst_env;
	while (sh->ptr_env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(sh->ptr_env->var, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(sh->ptr_env->content, 1);
		ft_putstr_fd("\"\n", 1);
		sh->ptr_env = sh->ptr_env->next;
	}
}

static void	ft_sort_export(t_sh *sh)
{
	char		*tmp;
	char		**tab;
	int			size;
	int			i;
	int			j;
	sh->ptr_env = sh->lst_env;

	i = -1;
	size = env_lstsize(sh->ptr_env);
	tab = lst_to_tab(sh->ptr_env);
	if (!tab)
		return ;
	while (++i < size)
	{
		j = i;
		while (++j < size)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
		}
	}
	print_export(sh, tab);
	free_tab(tab);
}

char *check_export(t_sh *sh, char *s1)
{
	int i;

	i = 0;
	while (s1[i] && s1[i] != '=')
		i++;
	return (NULL);
}

void ft_export(t_sh *sh)
{
	char *value;
	char *var;
	int equal_pos;
	
	value = NULL;
	var = NULL;
	equal_pos = 0;
	sh->ptr_cmd = sh->lst_cmd;
	while(sh->ptr_cmd)
	{
		if (!ft_strcmp(sh->ptr_cmd->cmd, "export"))
		{
			if (sh->ptr_cmd->next)
				sh->ptr_cmd = sh->ptr_cmd->next;
			if (!sh->ptr_cmd->next && !ft_strchr(sh->ptr_cmd->cmd, '='))
			{
				ft_sort_export(sh);
				return;
			}
		}
		value = ft_strchr(sh->ptr_cmd->cmd, '=');
		if (value)
			equal_pos = ft_strchr(sh->ptr_cmd->cmd, '=') - (char *)sh->ptr_cmd->cmd;
		if (equal_pos)
			var = ft_substr(sh->ptr_cmd->cmd, 0, equal_pos);
		if (ft_strlen(sh->ptr_cmd->cmd) > 1)
			value = ft_substr(sh->ptr_cmd->cmd, equal_pos + 1, ft_strlen(sh->ptr_cmd->cmd));
		else
			value = ft_substr(sh->ptr_cmd->cmd, equal_pos, ft_strlen(sh->ptr_cmd->cmd));
		if (!env_lstdupe(sh, var, value))
		{
			sh->ptr_env = sh->lst_env;
			env_lstaddback(&sh->ptr_env, env_lstnew(var, value));
		}
		sh->ptr_cmd = sh->ptr_cmd->next;
	}
} 

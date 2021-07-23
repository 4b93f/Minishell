/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 14:26:34 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/23 17:19:16 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

static char	**lst_to_tab(t_lst_env *lst)
{
	char		**ptr;
	t_lst_env	*arg_ptr;
	int			size;

	ptr = NULL;
	size = env_lstsize(lst);
	arg_ptr = lst;
	ptr = ft_calloc(sizeof(char *), size + 1);
	if (!ptr)
		return (NULL);
	size = -1;
	while (arg_ptr)
	{
		ptr[++size] = ft_strdup(arg_ptr->var);
		if (!ptr)
			return (free_tab(ptr));
		arg_ptr = arg_ptr->next;
	}
	return (ptr);
}


void print_export(t_sh *sh, char **tab)
{
	int i;

	i = 0;
	sh->ptr_env = sh->lst_env;
	while (sh->ptr_cmd && tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		write(1, "=", 1);
		ft_putendl_fd(sh->ptr_env->content, 1);
		sh->ptr_env = sh->ptr_env->next;
		i++;
	}
}

static void	ft_sort_export(t_sh *sh)
{
	char		*tmp;
	char		**tab;
	int			size;
	int			i;
	int			j;

	i = -1;
	size = env_lstsize(sh->lst_env);
	tab = lst_to_tab(sh->lst_env);
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
	equal_pos = 0;
	sh->ptr_cmd = sh->lst_cmd;
	if (!ft_strcmp(sh->ptr_cmd->cmd, "export"))
	{
		if (!sh->ptr_cmd->next)
			ft_sort_export(sh);
	}
	else
	{
		sh->ptr_cmd = sh->ptr_cmd->next;
		printf("!\n");
		value = ft_strchr(sh->ptr_cmd->cmd, '=');
		if (value)
			equal_pos = ft_strchr(sh->ptr_cmd->cmd, '=') - (char *)sh->ptr_cmd->cmd;
		if (equal_pos)
			var = ft_substr(sh->ptr_cmd->cmd, 0, equal_pos - 1);	
		printf("value?=[%s]\n", var);
	}
	
} 

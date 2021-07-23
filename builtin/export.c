/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 14:26:34 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/23 16:29:29 by chly-huc         ###   ########.fr       */
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
	free_tab(tab);
}

static char *check_export(t_sh *sh, char *s1)
{
	int i;

	i = 0;
	while (s1[i] != '=')
		i++;
	return (s1 + i);	
}


void ft_export(t_sh *sh)
{
	char *str;
	sh->ptr_cmd = sh->lst_cmd;
	if (ft_strcmp(sh->ptr_cmd->cmd, "export"))
	{
		sh->ptr_cmd = sh->ptr_cmd->next;
		str = check_export(sh, sh->ptr_cmd->cmd);
		if (!str)
			return;
	}
} 

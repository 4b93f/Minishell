/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:47:44 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/10 17:49:42 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct/struct.h"

int	str_spechar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			return (1);
	return (0);
}

int	is_sep(int c)
{
	return (c == ';' || c == ' ' || c == '<' || c == '>' || c == '|');
}

int	str_sep(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == ';' || str[i] == '<' || str[i] == '>' || str[i] == '|')
			return (1);
	return (0);
}

void	print_export(t_sh *sh, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", sh->fd_out);
		ft_putstr_fd(tab[i], sh->fd_out);
		ft_putstr_fd("=\"", sh->fd_out);
		ft_putstr_fd(env_lstcontent(sh, tab[i]), sh->fd_out);
		ft_putstr_fd("\"\n", sh->fd_out);
		i++;
	}
}

void	ft_sort_export(t_sh *sh, int i, char *tmp)
{
	char		**tab;
	int			size;
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

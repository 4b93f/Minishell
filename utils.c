/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:15:01 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/15 16:35:22 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	*free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	if (tab)
		free(tab);
	tab = NULL;
	return (NULL);
}

char	*ft_strjoinfree(const char *s1, const char *s2)
{
	char	*tab;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1)
		return (ft_strdup(s2));
	tab = malloc(sizeof(char) * ft_strlen((char *)s1)
			+ ft_strlen((char *)s2) + 1);
	if (!tab)
		return (NULL);
	while (s1[++i])
		tab[i] = s1[i];
	while (s2[++j])
		tab[j + i] = s2[j];
	tab[i + j] = '\0';
	free((char *)s1);
	return (tab);
}

t_env_lst	*env_lst_finder(t_env_lst *lst, char *var)
{
	t_env_lst	*ptr_lst;
	t_env_lst	*tmp;

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

void	print_env(t_env_lst *lst, int fd, t_sh *sh)
{
	t_env_lst	*ptr_lst;

	ptr_lst = lst;
	while (ptr_lst)
	{
		if (ptr_lst->var && ft_strcmp(ptr_lst->var, "?"))
		{
			ft_putstr_fd(ptr_lst->var, fd);
			write(fd, "=", 1);
			ft_putstr_fd(ptr_lst->content, fd);
			write(fd, "\n", 1);
		}
		ptr_lst = ptr_lst->next;
	}
	free(env_lst_finder(sh->env_lst, "?")->content);
	env_lst_finder(sh->env_lst, "?")->content = ft_itoa(0);
}

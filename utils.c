/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:15:01 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/03 01:45:37 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_tab(char **tab)
{
	int i;

	i = -1;
	while(tab && tab[++i])
		free(tab[i]);
	if (tab)
		free(tab);
	tab = NULL;
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
	if (!(tab = malloc(sizeof(char) * ft_strlen((char*)s1)
					+ ft_strlen((char*)s2) + 1)))
		return (NULL);
	while (s1[++i])
		tab[i] = s1[i];
	while (s2[++j])
		tab[j + i] = s2[j];
	tab[i + j] = '\0';
	free((char*)s1);
	return (tab);
}

/*
**	env_lst_finder
**
**	Renvoie un pointer sur le chainon (lst) correspondant.
*/

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

void	print_env(t_env_lst *lst, int fd)
{
	t_env_lst	*ptr_lst;
	
	int	i = 0;

	ptr_lst = lst;
	while (ptr_lst)
	{
		if (ptr_lst->var && ft_strcmp(ptr_lst->var, "?"))
		{
			ft_putstr_fd(ptr_lst->var, fd);
			write(fd, "=", 1);
			ft_putstr_fd(ptr_lst->content, fd);
			if (fd < 3)
				write(fd, "\n", 1);
		}
		ptr_lst = ptr_lst->next;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = -1;
	while(tab && tab[++i])
		ft_putstr_fd(tab[i], 1);
}

int	ft_isspace(int c)
{
	return (c == 32 || (c > 8 && c < 14));
}

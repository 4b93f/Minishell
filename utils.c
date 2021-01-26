/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:15:01 by chly-huc          #+#    #+#             */
/*   Updated: 2021/01/26 01:38:08 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int tablen(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		i++;
	return (i);	
}

int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
			|| c == ' ')
		return (1);
	return (0);
}

void free_tab(char **tab)
{
	int i;

	i = -1;
	while(tab[++i])
		free(tab[i]);
	free(tab);
}

char **tabcpy(char **tab)
{
	char **new_tab;
	
	int i;
	new_tab = NULL;
	new_tab = (char**)malloc(sizeof(char*) * (tablen(tab) + 1));
	i = -1;
	while(tab[++i])
		new_tab[i] = ft_strdup(tab[i]);
	new_tab[i] = NULL;
	return(new_tab);
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

char	**ft_realloc(char **str, char *line)
{
	char	**cpy;
	int		i;

	cpy = NULL;
	i = 0;
	while (str[i] != NULL)
		i++;
	if (!(cpy = malloc(sizeof(char *) * (i + 2))))
		return(NULL);
	i = 0;
	while (str[i] != NULL)
	{
		cpy[i] = ft_strdup(str[i]);
		free(str[i]);
		i++;
	}
	cpy[i] = ft_strdup(line);
	cpy[i + 1] = NULL;
	free(str);
	return (cpy);
}

/*
**	env_lst_finder
**
**	Renvoie le content de la liste chainee (lst) a la variable 
**	correspondante (var).
*/

void	*env_lst_finder(t_env_lst *lst, char *var)
{
	t_env_lst	*ptr_lst;

	ptr_lst = lst;
	if (!ptr_lst || !var)
		return (NULL);
	while (ft_strcmp(ptr_lst->var, var))
		ptr_lst = ptr_lst->next;
	return (ptr_lst->content);
}

void	print_env(t_env_lst *lst, int fd)
{
	t_env_lst	*ptr_lst;

	ptr_lst = lst;
	while (ptr_lst)
	{
		ft_putstr_fd(ptr_lst->var, fd);
		write(fd, "=", 1);
		ft_putstr_fd(ptr_lst->content, fd);
		write(fd, "\n", 1); //a supprimer en cas de pipe.
	}
}

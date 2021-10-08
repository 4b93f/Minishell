/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 16:58:29 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/08 13:56:15 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct/struct.h"

int str_spechar(char *str)
{
	int i;

	i = -1;
	while(str[++i])
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			return(1);
	return(0);	
}

int is_sep(int c)
{
    return (c == ';' || c == ' ' || c == '<' || c == '>' || c == '|');
}

int str_sep(char *str)
{
	int i;
	
	i = -1;
	while (str[++i])
		if (str[i] == ';' || str[i] == '<' || str[i] == '>' || str[i] == '|')
			return (1);
	return (0);
}

void	ft_print_lst(t_lst_cmd *lst)
{
	
	if (!lst)
		return ;
	while (lst)
	{
		//printf("!\n");
		printf("[%p] - [%s] - [%d]\n",lst->cmd, lst->cmd, lst->type);
		lst = lst->next;
	}
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

char	*get_actual_path(void)
{
	char	*buf;
	char	*str;
    size_t	size;

	buf = NULL;
	str = NULL;
    size = 10000;
	str = getcwd(buf, size);
	return (str);
}

void ft_print_tab(char **str)
{
	int i;

	i = -1;
	while(str[++i])
		printf("[%s]\n", str[i]);
}


char	*ft_search_path(t_sh *sh, char *str)
{
	struct stat	buffer;
	char		*tmp;
	int			i;

	i = -1;
	while (sh->all_path && sh->all_path[++i])
	{
		tmp = ft_strjoin(sh->all_path[i], str);
		if (!tmp)
			return (NULL);
		if (!stat(tmp, &buffer))
		{
			free(tmp);
			return (sh->all_path[i]);
		}
		free(tmp);
	}
	return (NULL);
}

void	get_all_path(t_sh *sh)
{
	int			i;

	i = -1;
	sh->ptr_env = sh->lst_env;
	while (sh->ptr_env && ft_strcmp(sh->ptr_env->var, "PATH"))
		sh->ptr_env = sh->ptr_env->next;
	if (!sh->ptr_env)
		return ;
	//printf("!\n");
	//printf("%s\n", sh->ptr_env->content);
	sh->all_path = ft_split(sh->ptr_env->content, ':');

	if (!sh->all_path)
		return ;
	while (sh->all_path[++i])
	{
		sh->free_ptr = sh->all_path[i];
		sh->all_path[i] = ft_strjoin(sh->all_path[i], "/");
		free(sh->free_ptr);
	}
}

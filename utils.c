/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 16:58:29 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/10 17:50:15 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct/struct.h"

///////////////////////////////////////////// FOR TESTING
void	ft_print_lst(t_lst_cmd *lst)
{
	
	if (!lst)
		return ;
	while (lst)
	{
		printf("[%p] - [%s] - [%d]\n",lst->cmd, lst->cmd, lst->type);
		lst = lst->next;
	}
}
////////////////////////////////////////////////////////////////////////

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

char	**lst_to_tab(t_lst_env *lst)
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
			return (NULL);
		arg_ptr = arg_ptr->next;
	}
	return (ptr);
}

void sigret(int c)
{
	(void)c;
	exit(0);	
}

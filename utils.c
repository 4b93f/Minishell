/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 16:58:29 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/23 22:44:33 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct/struct.h"

int is_sep(int c)
{
    return (c == ';' || c == ' ' || c == '<' || c == '>' || c == '|');
}

void	ft_print_lst(t_lst_cmd *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		printf("[%s]\n", lst->cmd);
		lst = lst->next;
	}
}

void	ft_print_env(t_lst_env *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		printf("{%s}", lst->var);
		printf("{%s}\n", lst->content);
		lst = lst->next;
	}
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
			return (free_tab(ptr));
		arg_ptr = arg_ptr->next;
	}
	return (ptr);
}

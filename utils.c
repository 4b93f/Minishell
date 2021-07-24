/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 16:58:29 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/25 00:39:53 by chly-huc         ###   ########.fr       */
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
			return (NULL);
		arg_ptr = arg_ptr->next;
	}
	return (ptr);
}

char	*ft_search_path(t_sh *sh)
{
	struct stat	buffer;
	char		*tmp;
	int			i;

	i = -1;
	while (sh->all_path && sh->all_path[++i])
	{
		tmp = ft_strjoin(sh->all_path[i], sh->lst_cmd->cmd);
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
		//printf("<<%s>>\n", sh->all_path[i]);
		sh->all_path[i] = ft_strjoin(sh->all_path[i], "/");
	}
}

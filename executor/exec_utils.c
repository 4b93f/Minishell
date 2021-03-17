/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 21:57:40 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/17 16:48:23 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include "executor.h"

static char	*ft_multi_var(char *str, t_sh *sh)
{
	char		**ptr;
	int			i;
	char		*ret;
	char		*tmp;
	// char		*tmpb;
	t_env_lst	*lst;

	i = 0;
	ret = NULL;
	ptr = ft_split(str, '$');
	while (ptr && ptr[i])
	{
		lst = env_lst_finder(sh->env_lst, ptr[i]);
		if(lst)
		{
			tmp = ret;
			ret = ft_strjoin(ret, lst->content);
			if (!ret && lst->content)
				ft_error(MALLOC_ERROR, sh, 1);
			free(tmp);
		}
		i++;
	}
	free_tab(ptr);
	return (ret);
}

/*
**	Detecte si str est une variable d'env ou non et renvoie le resultat aproprie.
*/

char	*ft_is_var(char *str, t_sh *sh)
{
	t_env_lst	*ptr;
	char		*ptr_str;
	
	ptr = NULL;
	ptr_str = NULL;
	if (!str)
		return (NULL);
	if (str[0] == '$')
		return (ft_multi_var(str, sh));
	else if (str[0] == '~')
	{
		ptr = env_lst_finder(sh->env_lst, "HOME");
		if (ptr)
			return (rm_guim(ptr->content));
		else
			return (NULL);
	}
	ptr_str = ft_strdup(str);
	return (ptr_str);
}

char	*rm_guim(char *ptr)
{
	char	*str;

	if (!ptr)
		return (NULL);
	if (ptr[0] == '\'')
	{
		str = ft_strtrim(ptr, "\'");
		free(ptr);	
	}
	else if (ptr[0] == '\"')
	{
		str = ft_strtrim(ptr, "\"");
		free(ptr);
	}
	else
		return (ptr);
	ptr = NULL;
	return (str);
}

void	ft_portal(t_sh *sh, int ret, int pid, int fd[2])
{
	char	*ptr;

	if (!pid)
	{
		close(fd[0]);
		ptr = ft_itoa(ret);
		write(fd[1], ptr, ft_strlen(ptr));
		free(ptr);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		ptr = calloc(sizeof(char), 11);
		if (!ptr)
			ft_error(MALLOC_ERROR, sh, 0);
		free(env_lst_finder(sh->env_lst, "?")->content);
		if (read(fd[0], ptr, 10) == -1)
			perror("ft_portal: read fail");
		env_lst_finder(sh->env_lst, "?")->content = ft_strdup(ptr);
		free(ptr);
		close(fd[0]);
	}
}

/*
**	Convert string of command in double tab.
*/

char	**lst_db_tab(t_cmd_lst *cmd)
{
	char	**ptr;
	t_list	*arg_ptr;
	int		size;

	ptr = NULL;
	size = ft_lstsize(cmd->str);
	arg_ptr = cmd->str;
	ptr = ft_calloc(sizeof(char *), size + 2);
	if (!ptr)
		return (NULL);
	size = -1;
	ptr[++size] = ft_strdup(cmd->cmd_str);
	if (!ptr)
		return (free_tab(ptr));
	while(arg_ptr)
	{
		arg_ptr->content = rm_guim(arg_ptr->content);
		ptr[++size] = ft_strdup(arg_ptr->content);
		if (!ptr)
			return (free_tab(ptr));
		arg_ptr = arg_ptr->next;
	}
	return (ptr);
}

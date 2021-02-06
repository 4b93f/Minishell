/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 21:57:40 by jsilance          #+#    #+#             */
/*   Updated: 2021/02/06 19:59:56 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			// tmpb = rm_guim(ft_strdup(lst->content));
			ret = ft_strjoin(ret, lst->content);
			// ret = ft_strjoin(ret, tmpb);
			// free(tmpb);
			free(tmp);
		}
		i++;
	}
	free_tab(ptr);
	return (ret);
}

/*
**	Detecte si str est une variable d'env ou non et renvoie le resultat aproprie.
**	/!\	gerer le $?.
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

	str = ft_strtrim(ptr, "\'\"");
	free(ptr);
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

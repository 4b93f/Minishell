/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 21:57:40 by jsilance          #+#    #+#             */
/*   Updated: 2021/02/02 00:22:47 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Detecte si str est une variable d'env ou non et renvoie le resultat aproprie.
**	/!\	gerer le $?.
*/

char	*ft_is_var(char *str, t_sh *sh)
{
	t_env_lst	*ptr;
	
	ptr = NULL;
	if (!str)
		return (NULL);
	if (str[0] == '$')
	{
		ptr = env_lst_finder(sh->env_lst, &str[1]);
		if (ptr)
			return (ptr->content);
		else
			return (NULL);
	}
	else if (str[0] == '~')
	{
		ptr = env_lst_finder(sh->env_lst, "HOME");
		if (ptr)
			return (ptr->content);
		else
			return (NULL);
	}
	return (str);
}

char	*rm_guim(char *ptr)
{
	char	*str;

	str = ft_strtrim(ptr, "\'\"");
	free(ptr);
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
		if (!(ptr = calloc(sizeof(char), 11)))
			ft_error(MALLOC_ERROR, sh, 0);
		free(env_lst_finder(sh->env_lst, "?")->content);
		read(fd[0], ptr, 10);
		env_lst_finder(sh->env_lst, "?")->content = ft_strdup(ptr);
		free(ptr);
		close(fd[0]);
	}
}

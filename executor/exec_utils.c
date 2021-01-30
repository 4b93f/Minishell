/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 21:57:40 by jsilance          #+#    #+#             */
/*   Updated: 2021/01/30 00:46:29 by jsilance         ###   ########.fr       */
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

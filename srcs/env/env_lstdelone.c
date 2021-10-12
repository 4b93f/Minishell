/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:28:51 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/10 18:42:58 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void	env_lstdelone(t_lst_env *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	if (lst->var)
		del(lst->var);
	if (lst->content)
		del(lst->content);
	lst->var = NULL;
	lst->content = NULL;
	free(lst);
}

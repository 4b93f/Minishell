/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:28:51 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/12 15:35:48 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	env_lstdelone(t_lst_env *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	if (lst->var)
		del(lst->var);
	if (lst->content)
		del(lst->content);
	free(lst);
}
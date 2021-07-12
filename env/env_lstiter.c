/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:36:31 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/12 15:37:04 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	env_lstiter(t_lst_env *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

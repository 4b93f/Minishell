/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:27:02 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/12 15:33:42 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	env_lstclear(t_lst_env **lst, void (*del)(void*))
{
	t_lst_env	*ptr;
	t_lst_env	*tmp;

	if (!lst || !*lst || !del)
		return ;
	tmp = NULL;
	ptr = *lst;
	while (ptr)
	{
		tmp = ptr->next;
		env_lstdelone(ptr, (*del));
		ptr = tmp;
	}
	*lst = NULL;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envlstclear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 23:28:38 by jsilance          #+#    #+#             */
/*   Updated: 2021/02/15 21:12:10 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env_cl.h"

void	ft_env_lstclear(t_env_lst **lst, void (*del)(void*))
{
	t_env_lst	*ptr;
	t_env_lst	*tmp;

	if (!lst || !*lst || !del)
		return ;
	tmp = NULL;
	ptr = *lst;
	while (ptr)
	{
		tmp = ptr->next;
		ft_env_lstdelone(ptr, (*del));
		free(ptr);
		ptr = tmp;
	}
	*lst = NULL;
}

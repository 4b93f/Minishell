/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envlstdelone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:52:28 by jsilance          #+#    #+#             */
/*   Updated: 2021/01/29 23:58:22 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env_cl.h"

void	ft_env_lstdelone(t_env_lst *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->var);
	del(lst->content);
	lst->var = NULL;
	lst->content = NULL;
	// free(lst);
}

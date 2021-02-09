/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlstdelone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:52:28 by jsilance          #+#    #+#             */
/*   Updated: 2021/02/09 19:09:33 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cmd_cl.h"

void	ft_cmd_lstdelone(t_cmd_lst *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	ft_lstclear(&lst->str, free);
	ft_lstclear(&lst->red_file, free);
	del(lst->flags);
	del(lst->cmd_str);
	free(lst);
}

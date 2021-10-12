/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 02:44:47 by jsilance          #+#    #+#             */
/*   Updated: 2021/10/10 19:08:35 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

t_lst_cmd	*cmd_lstnew(void *content, int type, int redirected)
{
	t_lst_cmd	*ptr;

	ptr = ((t_lst_cmd *)malloc(sizeof(t_lst_cmd)));
	if (!ptr)
		return (NULL);
	ptr->cmd = content;
	ptr->type = type;
	ptr->redirected = redirected;
	ptr->next = NULL;
	return (ptr);
}

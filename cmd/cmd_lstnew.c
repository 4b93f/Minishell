/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 02:44:47 by jsilance          #+#    #+#             */
/*   Updated: 2021/10/06 20:58:29 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_lst_cmd	*cmd_lstnew(void *content, int type)
{
	t_lst_cmd	*ptr;

	if (!(ptr = (t_lst_cmd *)malloc(sizeof(t_lst_cmd))))
		return (NULL);
	ptr->cmd = content;
	ptr->type = type;
	ptr->next = NULL;
	return (ptr);
}

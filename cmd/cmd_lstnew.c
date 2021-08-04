/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 02:44:47 by jsilance          #+#    #+#             */
/*   Updated: 2021/08/04 15:57:36 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_lst_cmd	*cmd_lstnew(void *content)
{
	t_lst_cmd	*ptr;

	if (!(ptr = (t_lst_cmd *)malloc(sizeof(t_lst_cmd))))
		return (NULL);
	ptr->cmd = content;
	ptr->next = NULL;
	return (ptr);
}

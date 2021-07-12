/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstaddfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 04:14:57 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/12 15:14:07 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	cmd_lstadd_front(t_lst_cmd **alst, t_lst_cmd *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

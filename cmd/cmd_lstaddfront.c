/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstaddfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 04:14:57 by jsilance          #+#    #+#             */
/*   Updated: 2021/10/10 18:41:52 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void	cmd_lstadd_front(t_lst_cmd **alst, t_lst_cmd *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstaddback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 05:00:11 by jsilance          #+#    #+#             */
/*   Updated: 2021/08/04 15:57:54 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	cmd_lstaddback(t_lst_cmd **alst, t_lst_cmd *new)
{
	if (alst && *alst)
		cmd_lstlast(*alst)->next = new;
	else if (alst)
		*alst = new;
}

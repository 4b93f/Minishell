/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlstadd_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 04:14:57 by jsilance          #+#    #+#             */
/*   Updated: 2020/12/09 03:48:31 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cmd_cl.h"

void	ft_cmd_lstadd_front(t_cmd_lst **alst, t_cmd_lst *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

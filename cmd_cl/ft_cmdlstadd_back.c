/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlstadd_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 05:00:11 by jsilance          #+#    #+#             */
/*   Updated: 2020/12/09 03:47:51 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cmd_cl.h"

void	ft_cmd_lstadd_back(t_cmd_lst **alst, t_cmd_lst *new)
{
	if (alst && *alst)
		ft_cmd_lstlast(*alst)->next = new;
	else if (alst)
		*alst = new;
}

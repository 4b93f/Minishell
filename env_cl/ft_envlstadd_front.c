/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlstadd_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 04:14:57 by jsilance          #+#    #+#             */
/*   Updated: 2021/01/23 19:49:15 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env_cl.h"

void	ft_env_lstadd_front(t_env_lst **alst, t_env_lst *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

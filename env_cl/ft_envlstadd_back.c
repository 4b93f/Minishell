/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlstadd_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 05:00:11 by jsilance          #+#    #+#             */
/*   Updated: 2021/01/23 19:48:52 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env_cl.h"

void	ft_env_lstadd_back(t_env_lst **alst, t_env_lst *new)
{
	if (alst && *alst)
		ft_env_lstlast(*alst)->next = new;
	else if (alst)
		*alst = new;
}

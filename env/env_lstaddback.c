/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstaddback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:22:45 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/20 17:02:58 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	env_lstaddback(t_lst_env **alst, t_lst_env *new)
{
	if (alst && *alst)
		env_lstlast(*alst)->next = new;
	else if (alst)
		*alst = new;
}
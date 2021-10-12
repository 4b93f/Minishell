/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstaddback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:22:45 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/10 20:36:27 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void	env_lstaddback(t_lst_env **alst, t_lst_env *new)
{
	if (alst && *alst)
		env_lstlast(*alst)->next = new;
	else if (alst)
		*alst = new;
}

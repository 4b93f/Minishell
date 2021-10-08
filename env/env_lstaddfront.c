/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstaddfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:25:37 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/08 09:52:07 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	env_lstadd_front(t_lst_env **alst, t_lst_env *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

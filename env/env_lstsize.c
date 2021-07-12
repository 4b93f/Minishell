/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:43:02 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/12 15:43:21 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	env_lstsize(t_lst_env *lst)
{
	int	count;

	count = 0;
	while (lst && ++count)
		lst = lst->next;
	return (count);
}
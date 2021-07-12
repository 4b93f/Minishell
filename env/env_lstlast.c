/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstlast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:43:40 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/12 15:43:50 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_lst_env	*env_last(t_lst_env *lst)
{
	t_lst_env	*ptr;

	ptr = NULL;
	while (lst)
	{
		ptr = lst;
		lst = lst->next;
	}
	return (ptr);
}
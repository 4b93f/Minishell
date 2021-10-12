/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:38:09 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/11 22:33:28 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

t_lst_env	*env_lstnew(void *var, void *content)
{
	t_lst_env	*ptr;

	ptr = ((t_lst_env *)malloc(sizeof(t_lst_env)));
	if (!ptr)
		return (NULL);
	ptr->var = ft_strdup(var);
	ptr->content = ft_strdup(content);
	ptr->next = NULL;
	return (ptr);
}

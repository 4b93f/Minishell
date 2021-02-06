/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envlstnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 02:44:47 by jsilance          #+#    #+#             */
/*   Updated: 2021/02/05 23:29:36 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env_cl.h"

t_env_lst	*ft_env_lstnew(void *var, void *content)
{
	t_env_lst	*ptr;
	
	ptr = malloc(sizeof(t_env_lst));
	if (!ptr)
		return (NULL);
	ptr->var = var;
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlstnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 02:44:47 by jsilance          #+#    #+#             */
/*   Updated: 2021/01/23 19:52:39 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env_cl.h"

t_env_lst	*ft_env_lstnew(void *var, void *content)
{
	t_env_lst	*ptr;

	if (!(ptr = (t_env_lst *)malloc(sizeof(t_env_lst))))
		return (NULL);
	ptr->var = var;
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}

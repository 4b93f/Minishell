/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:02:38 by chly-huc          #+#    #+#             */
/*   Updated: 2021/05/08 17:06:51 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <term.h>
#include <curses.h>
#include <termios.h>

t_history	*ft_historylast(t_history *lst)
{
	t_history	*ptr;

	ptr = NULL;
	while (lst)
	{
		ptr = lst;
		lst = lst->next;
	}
	return (ptr);
}

void	ft_historyadd_front(t_history **alst, t_history *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

t_history	*ft_historynew(void *content)
{
	t_history	*ptr;
	
	ptr = malloc(sizeof(t_history));
	if (!ptr)
		return (NULL);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}
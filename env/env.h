/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:23:54 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/21 15:57:29 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
#define ENV_H

typedef struct	s_lst_env
{
	char		*var;
	void		*content;
	
	void		*next;
}				t_lst_env;

#include "../struct/struct.h"

void	env_lstaddback(t_lst_env **alst, t_lst_env *new);
void	env_lstadd_front(t_lst_env **alst, t_lst_env *new);
void	env_lstclear(t_lst_env **lst, void (*del)(void*));
void	env_lstdelone(t_lst_env *lst, void (*del)(void*));
void	env_lstiter(t_lst_env *lst, void (*f)(void *));
t_lst_env	*env_lstlast(t_lst_env *lst);
t_lst_env	*env_lstnew(void *var, void *content);
int	env_lstsize(t_lst_env *lst);
int is_sep(int c);

#endif
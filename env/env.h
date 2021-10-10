/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:23:54 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/10 18:20:04 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_lst_env
{
	char		*var;
	void		*next;
	void		*content;
}				t_lst_env;

# include "../struct/struct.h"

int			is_sep(int c);
int			env_lstsize(t_lst_env *lst);
t_lst_env	*env_lstlast(t_lst_env *lst);
char		**lst_to_tab(t_lst_env *lst);
t_lst_env	*env_lstnew(void *var, void *content);
void		env_lstiter(t_lst_env *lst, void (*f)(void *));
void		env_lstaddback(t_lst_env **alst, t_lst_env *new);
void		env_lstclear(t_lst_env **lst, void (*del)(void*));
void		env_lstdelone(t_lst_env *lst, void (*del)(void*));
void		env_lstadd_front(t_lst_env **alst, t_lst_env *new);

#endif
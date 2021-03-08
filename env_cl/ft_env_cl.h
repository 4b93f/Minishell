/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_cl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:29:21 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/08 12:52:02 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_CL_H

# define FT_ENV_CL_H

# include "../libft/libft.h"

typedef struct	s_env_lst
{
	char		*var;
	void		*content;
	
	void		*next;
}				t_env_lst;

void		ft_env_lstadd_back(t_env_lst **alst, t_env_lst *new);
void		ft_env_lstadd_front(t_env_lst **alst, t_env_lst *new);
void		ft_env_lstclear(t_env_lst **lst, void (*del)(void*));
void		ft_env_lstdelone(t_env_lst *lst, void (*del)(void*));
void		ft_env_lstiter(t_env_lst *lst, void (*f)(void *));
t_env_lst	*ft_env_lstlast(t_env_lst *lst);
t_env_lst	*ft_env_lstnew(void *var, void *content);
int			ft_env_lstsize(t_env_lst *lst);

#endif
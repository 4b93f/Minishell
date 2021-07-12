/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:29:21 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/12 22:23:13 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
#define CMD_H
#include "stdlib.h"

typedef struct	s_lst_cmd
{
	char	*cmd;
	
	void	*next;
}				t_lst_cmd;

void		cmd_lstaddback(t_lst_cmd **alst, t_lst_cmd *new);
void		cmd_lstaddfront(t_lst_cmd **alst, t_lst_cmd *new);
void		cmd_lstclear(t_lst_cmd **lst, void (*del)(void*));
void		cmd_lstdelone(t_lst_cmd *lst, void (*del)(void*));
void		cmd_lstiter(t_lst_cmd *lst, void (*f)(void *));
t_lst_cmd	*cmd_lstlast(t_lst_cmd *lst);
t_lst_cmd	*cmd_lstnew(void *content);
int			cmd_lstsize(t_lst_cmd *lst);

#endif
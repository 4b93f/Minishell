/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_cl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:29:21 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/15 20:28:31 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CMD_CL_H

# define FT_CMD_CL_H

# include "../libft/libft.h"

typedef struct s_cmd_lst
{
	int			cmd_index;
	char		*cmd_str;
	char		*flags;

	int			pipe_in;
	int			fd_pipe_in;

	int			pipe_out;
	int			fd_pipe_out;
	t_list		*red_file;

	t_list		*str;
	int			pid;
	pid_t		child_pid;
	void		*next;
}				t_cmd_lst;

void		ft_cmd_lstadd_back(t_cmd_lst **alst, t_cmd_lst *new);
void		ft_cmd_lstadd_front(t_cmd_lst **alst, t_cmd_lst *new);
void		ft_cmd_lstclear(t_cmd_lst **lst, void (*del)(void*));
void		ft_cmd_lstdelone(t_cmd_lst *lst, void (*del)(void*));
void		ft_cmd_lstiter(t_cmd_lst *lst, void (*f)(void *));
t_cmd_lst	*ft_cmd_lstlast(t_cmd_lst *lst);
t_cmd_lst	*ft_cmd_lstnew(void *str, void *flag, int index);
int			ft_cmd_lstsize(t_cmd_lst *lst);

#endif
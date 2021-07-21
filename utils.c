/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 16:58:29 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/21 20:10:28 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct/struct.h"

int is_sep(int c)
{
    return (c == ';' || c == ' ' || c == '<' || c == '>' || c == '|');
}

//void	ft_print_lst(t_lst_env *lst)
//{
//	if (!lst)
//		return ;
//	while (lst)
//	{
//		ft_putendl_fd(lst->var, 1);
//		ft_putendl_fd(lst->content, 1);
//		lst = lst->next;
//	}
//}

char	*get_actual_path(void)
{
	char	*buf;
	char	*str;
    size_t	size;

	buf = NULL;
	str = NULL;
    size = 10000;
	str = getcwd(buf, size);
	return (str);
}

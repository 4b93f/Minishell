/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:41:11 by chly-huc          #+#    #+#             */
/*   Updated: 2021/08/12 18:11:34 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void ft_pwd(t_sh *sh)
{
	char *free_ptr;
	(void)sh;
	free_ptr = get_actual_path();	
	ft_putendl_fd(free_ptr, 1);
	free(free_ptr);
}
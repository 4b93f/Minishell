/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:41:11 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/08 09:47:57 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void	ft_pwd(void)
{
	char	*free_ptr;

	free_ptr = get_actual_path();
	ft_putendl_fd(free_ptr, 1);
	free(free_ptr);
}

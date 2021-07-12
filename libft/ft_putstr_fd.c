/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 19:15:13 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/09 23:12:38 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s || fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
	return ;
}
/*
** Ecrire une chaine de caractère dans un fichier donné
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:24:18 by chly-huc          #+#    #+#             */
/*   Updated: 2021/01/25 23:46:56 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (!(ptr = malloc(sizeof(char) * ((int)len + 1))))
		return (NULL);
	ft_strlcpy(ptr, s + start, ++len);
	return (ptr);
}

/*
** retourne une chaine de caractères issue de la chaine ’s’.
** Cette nouvelle chaine commence à l’index ’start’ et
** a pour taille maximale ’len’
*/

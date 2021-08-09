/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:05:20 by chly-huc          #+#    #+#             */
/*   Updated: 2021/08/09 21:51:00 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void is_quote_open(char *str, int *squote, int *dquote, int i)
{
	if (!str)
		return ;
	if (*squote == 1 && str[i] == '\'')
		*squote = FALSE;
	else if (*squote == 0 && str[i] == '\'')
		*squote = TRUE;
	if (*dquote == 1 && str[i] == '\"')
		*dquote = FALSE;
	else if (*dquote == 0 && str[i] == '\"')
		*dquote = TRUE;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtolst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:31:11 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/12 18:21:37 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"


void str_to_lst(char *str, t_sh *sh)
{
	int i;

	i = -1;

	while(str[++i] != ' ')
		;
	cmd_lstadd_back(&sh->cmd->cmd, cmd_lstnew(ft_substr(str, 0, i)));
	str = &str + i;
}
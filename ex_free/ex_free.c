/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:52:00 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/25 00:31:26 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void sh_free(t_sh *sh)
{
	cmd_lstclear(&sh->lst_cmd, free);
	free(sh->input_str);
	free_tab(sh->all_path);
	sh->all_path = NULL;
}
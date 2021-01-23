/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 13:33:54 by chly-huc          #+#    #+#             */
/*   Updated: 2021/01/23 15:31:21 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(t_sh *sh)
{
	int i;

	i = -1;
	free_tab(sh->all_path);
	free(sh->input_str);
	free(sh->actual_pwd);
	free(sh->old_pwd);
	free_tab(sh->env);
	free(sh->tmp);
	free(sh);
	exit(0);
}
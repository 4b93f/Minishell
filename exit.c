/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 13:33:54 by chly-huc          #+#    #+#             */
/*   Updated: 2020/12/08 13:37:06 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(t_sh *sh)
{
	int i;

	i = -1;
	free_tab(sh->all_path);
	free(sh->built_in);
	free(sh->actual_pwd);
	free(sh->old_pwd);
	free_tab(sh->env);
	free(sh);
	exit(0);
}
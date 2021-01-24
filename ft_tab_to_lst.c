/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_to_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 22:54:42 by jsilance          #+#    #+#             */
/*   Updated: 2021/01/24 02:27:37 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_to_lst(char **env, t_sh *sh)
{
	int		i;
	int		equal_pos;
	char	*var;
	char	*value;

	i = -1;
	while (env && env[++i])
	{
		equal_pos = ft_strchr(env[i], '=');
		var = ft_substr(env[i], 0, equal_pos);
		value = ft_substr(env[i], equal_pos + 1, ft_strlen(env[i]));
		ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(var, value));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_to_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 22:54:42 by jsilance          #+#    #+#             */
/*   Updated: 2021/02/05 21:52:20 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_to_lst(char **env, t_sh *sh)
{
	int		i;
	int		equal_pos;
	char	*var;
	char	*value;
	t_env_lst	*new;

	i = -1;
	while (env && env[++i])
	{
		equal_pos = ft_strchr(env[i], '=') - env[i];
		var = ft_substr(env[i], 0, equal_pos - 1);
		if (!var)
			ft_error(MALLOC_ERROR, sh, 0);
		value = ft_substr(env[i], equal_pos + 1, ft_strlen(env[i]));
		if (!value)
		{
			free(var);
			ft_error(MALLOC_ERROR, sh, 0);
		}
		new = ft_env_lstnew(var, value);
		if (!new)
		{
			free(var);
			free(value);
			ft_error(MALLOC_ERROR, sh, 0);
		}
		ft_env_lstadd_back(&sh->env_lst, new);
	}
}

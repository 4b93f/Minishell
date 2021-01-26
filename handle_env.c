/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 13:31:30 by chly-huc          #+#    #+#             */
/*   Updated: 2021/01/26 01:42:53 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void create_env(t_sh *sh, char *new_env)
{
	char *tmp;

	tmp = ft_strdup(new_env);
	if (!ft_strchr(new_env, '='))
	{
		free(tmp);
		tmp = ft_strjoin(new_env, "=");
	}
	sh->env = ft_realloc(sh->env, tmp);
	free(tmp);	
}
*/

/*
char **delete_env(t_sh *sh, char *delete_env, int len)
{
	char **new_tab;
	int i;
	int k;

	i = 0;
	k = 0;
	new_tab = malloc(sizeof(char*) * len);
	while(len--)
	{
		if (strncmp(sh->env[k], delete_env, ft_strlen(delete_env)))
		{
			new_tab[i] = ft_strdup(sh->env[k]);
			i++;
		}
		else
			i--;
		free(sh->env[k]);
		k++;
	}
	free(sh->env);
	new_tab[++i] = NULL;
	return(new_tab);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarz2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:01:48 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/12 17:02:37 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

char	*dollar_cut(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_sep(str[i]) && str[i] != '=')
		i++;
	if (i == 0)
		return (ft_strdup("$"));
	return (ft_substr(str, 0, i));
}

char	*dollar_pass(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	if (str[i] == '$')
		i++;
	if (str[i] == '?')
		i++;
	while (str[i] && !is_sep(str[i]) && str[i] != '='
		&& (ft_isalpha(str[i]) || str[i] == '$'))
		i++;
	return (ft_substr(str, i, ft_strlen(str)));
}

char	*dollarz_value(t_sh *sh, char *str)
{
	t_lst_env	*envlst;
	char		*tmp;

	tmp = dollar_cut(str);
	if (!ft_strcmp(tmp, "$"))
		return (tmp);
	envlst = sh->lst_env;
	while (envlst)
	{	
		if (!ft_strncmp(tmp, envlst->var, ft_strlen(envlst->var)))
		{
			free(tmp);
			return (ft_strdup(envlst->content));
		}
		envlst = envlst->next;
	}
	free(tmp);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:02:20 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/08 10:23:59 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

static char	*dollar_cut(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_sep(str[i]) && str[i] != '=')
		i++;
	if (i == 0)
		return (ft_strdup("$"));
	return (ft_substr(str, 0, i));
}

static char	*dollar_pass(char *str)
{
	int	i;

	i = 0;
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
			return (envlst->content);
		}
		envlst = envlst->next;
	}
	return (NULL);
}

char	*dollar_swap(t_sh *sh, char *str, int i)
{
	char	*new;
	char	*tmp;
	char	*tmps;
	int		j;

	j = i;
	new = NULL;
	tmp = NULL;
	tmps = NULL;
	if (str[i - 1] && str[i - 1] == '\"')
		new = ft_substr(str, 0, i - 1);
	else
		new = ft_substr(str, 0, i);
	i++;
	tmp = dollarz_value(sh, (str + i));
	if (!tmp)
		tmp = ft_strdup(new);
	else
		tmp = ft_strjoin(new, tmp);
	while (str[j] != '$')
		j++;
	tmps = dollar_pass(str + j);
	str = ft_strjoin(tmp, tmps);
	return (str);
}

char	*dollarz(t_sh *sh, char *str)
{
	int	i;
	int	squote;
	int	dquote;

	i = 0;
	squote = 0;
	dquote = 0;
	while (str && str[i] && str[i] != ';')
	{
		is_quote_open(str, &squote, &dquote, i);
		if ((!squote && str[i] == '$'))
			str = dollar_swap(sh, str, i);
		i++;
	}
	return (str);
}

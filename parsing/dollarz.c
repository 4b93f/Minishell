/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:02:20 by chly-huc          #+#    #+#             */
/*   Updated: 2021/08/09 20:41:42 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

static char *dollar_cut(char *str)
{
	int i;

	i = 0;
	while (str[i] && !is_sep(str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

static char *dollar_pass(char *str)
{
	int i;

	i = 0;
	while (str[i] && !is_sep(str[i]))
		i++;
	return (ft_substr(str, i, ft_strlen(str)));
}

char *dollarz_value(t_sh *sh, char *str)
{
	int i;
	t_lst_env *envlst;
	char *tmp;

	i = 0;
	tmp = dollar_cut(str);
	envlst = sh->lst_env;
	while (envlst->next)
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

char *dollar_swap(t_sh *sh, char *str, int i)
{
	char *new;
	char *tmp;
	char *tmps;
	int j;

	j = i;
	if (str[i - 1] && str[i - 1] == '\"')
		new = ft_substr(str, 0, i - 1);
	else
		new = ft_substr(str, 0, i);
	new = ft_remove_char(new, '\'');
	i++;
	tmp = dollarz_value(sh, (str + i));
	if (!tmp)
		tmp = ft_strdup(new);
	else
		tmp = ft_strjoin(new, tmp);
	while(str[j] != '$')
		j++;
	tmps = dollar_pass(str + j);
	new = ft_substr(tmps, j, ft_strlen(str));
	str = ft_strjoin(tmp, tmps);
	return (str);
}

char *dollarz(t_sh *sh, char *str)
{
	int i;
	int squote;
	int dquote;

	i = 0;
	squote = 0;
	dquote = 0;
	while (str[i] && str[i] != ';')
	{
		is_quote_open(str, &squote, &dquote, i);
		if ((!squote && str[i] == '$'))
			str = dollar_swap(sh, str, i);
		i++;
	}
	return (str);
}
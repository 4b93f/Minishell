/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:02:20 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/12 17:02:00 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

char	*dollar_val(t_sh *sh, char *str, int i, char *new)
{
	char	*tmp;

	tmp = NULL;
	tmp = dollarz_value(sh, (str + i));
	if (!tmp)
		tmp = ft_strdup(new);
	else
	{
		sh->free_ptr = tmp;
		tmp = ft_strjoin(new, tmp);
	}
	return (tmp);
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
	if (str && str[i] && i != 0 && str[i - 1] && str[i - 1] == '\"')
		new = ft_substr(str, 0, i - 1);
	else
		new = ft_substr(str, 0, i);
	i++;
	tmp = dollar_val(sh, str, i, new);
	while (str && str[j] && str[j] != '$')
		j++;
	tmps = dollar_pass(str + j);
	free(str);
	str = ft_strjoin(tmp, tmps);
	free(new);
	free(tmps);
	free(tmp);
	return (str);
}

char	*dollarz(t_sh *sh, char *str)
{
	int		i;
	char	*tmp;
	int		squote;
	int		dquote;

	i = 0;
	squote = 0;
	dquote = 0;
	tmp = ft_strdup(str);
	while (tmp[i] && tmp[i] != ';')
	{
		is_quote_open(tmp, &squote, &dquote, i);
		if ((!squote && tmp[i] == '$'))
			tmp = dollar_swap(sh, tmp, i);
		i++;
		if (i >= ft_strlen(tmp))
			break ;
	}
	free(str);
	return (tmp);
}

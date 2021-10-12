/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtolst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:31:11 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/10 19:26:00 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

int	ver_quote(char *str)
{
	int	i;
	int	dquote;
	int	squote;

	i = 0;
	squote = 0;
	dquote = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		is_quote_open(str, &squote, &dquote, i);
		i++;
	}
	if (squote || dquote)
	{
		printf("Error, unclose quote detected\n");
		return (0);
	}
	return (1);
}

void	setup_type(int *i, int *type, char *str)
{
	*i = *i + 1;
	if (str[*i - 1] == '|')
		*type = PIPE;
	if (str[*i - 1] == '>')
		*type = RIGHT;
	else if (str[*i - 1] == str[*i] && str[*i - 1] == '>')
		*type = DRIGHT;
	else if (str[*i - 1] == str[*i] && str[*i - 1] == '<')
		*type = DLEFT;
	else if (str[*i - 1] == '<')
		*type = LEFT;
	while (str[*i - 1] == str[*i] && is_sep(str[*i]))
		*i = *i + 1;
}

void	handle_quote(char *tmp, int *i, int *squote, int *dquote)
{
	while (tmp[*i] && (!is_sep(tmp[*i]) || *squote || *dquote))
	{
		is_quote_open(tmp, squote, dquote, *i);
		*i = *i + 1;
	}
}

void	str_tolst(char *str, t_sh *sh, int i, int j)
{
	int		dquote;
	int		squote;
	int		type;
	char	*tmp;

	i = 0;
	tmp = str;
	squote = 0;
	dquote = 0;
	while (tmp && tmp[i])
	{
		j = i;
		type = 0;
		if (tmp[i] && !is_sep(tmp[i]))
			handle_quote(tmp, &i, &squote, &dquote);
		else if (tmp[i] == ' ')
		{
			i++;
			continue ;
		}
		else
			setup_type(&i, &type, str);
		cmd_lstaddback(&sh->lst_cmd,
			cmd_lstnew(ft_substr(tmp, j, i - j), type, 0));
	}
}

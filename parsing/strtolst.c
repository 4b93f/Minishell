/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtolst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:31:11 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/20 16:46:28 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

static void is_quote_open(char *str, int *squote, int *dquote, int i)
{
	if (!str)
		return (FALSE);
	if (squote == 1 && str[i] == '\'')
		squote = FALSE;
	else if (squote == 0 && str[i] == '\'')
		squote = TRUE;
	if (dquote == 1 && str[i] == '\"')
		dquote = FALSE;
	else if (dquote == 0 && str[i] == '\"')
		dquote = TRUE;
}

static char *dollar_verif(char *str)
{
	int i;

	i = 0;
	while (str[i] && !is_sep(str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

char *dollarz_value(t_sh *sh, char *str)
{
	int i;
	t_lst_env *envlst;
	char *tmp;

	i = 0;
	tmp = dollar_verif(str);
	envlst = sh->env;
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

	j = 0;
	new = ft_substr(str, 0, i);
	
	i++;
	tmp = dollarz_value(sh, (str + i));
	if (!tmp)
		return (NULL);
	else
		tmp = ft_strjoin(new, tmp);
	new = ft_substr(str, 0, i);
	new = ft_strjoin(tmp, new);
	return (new);
}

char *ft_dollarz(t_sh *sh, char *str)
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
		if (!squote && str[i] == '$')
		{
			str = dollar_swap(sh, str, i);
			printf("str = {%s}\n", str);
			exit(0);
		}
		else
			i++;
	}
	return (NULL);
}

char *str_to_lst(char *str, t_sh *sh)
{
	int squote = 0;
	int dquote = 0;
	
	int i;
	int j;

	j = 0;
	i = 0;
	// while(str[j] && (str[j] == ' '))

	i = j;
	if (str[i] == '|')
		while(str[i] == '|')
			i++;
	else
	{
		while(str[i] && str[i] != ' ')
		{
			i++;
			if (str[i] == '|')
				break;
		}
	}
	cmd_lstaddback(&sh->cmd, cmd_lstnew(ft_substr(str, j, i - j)));
	return (str + i);
}
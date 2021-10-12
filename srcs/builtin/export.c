/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 14:26:34 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/11 22:52:28 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

static int	check_export(char *s1)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != '=')
	{
		if (!ft_isalpha(s1[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	solo_export(t_sh *sh, int equal_pos, char *value)
{
	if (!ft_strcmp(sh->ptr_cmd->cmd, "export"))
	{
		sh->ptr_cmd = sh->ptr_cmd->next;
		if (!sh->ptr_cmd || !ft_strcmp(sh->ptr_cmd->cmd, "|"))
		{
			ft_sort_export(sh, equal_pos, value);
			exit_code(sh, 0);
			return (0);
		}
		if (check_export(sh->ptr_cmd->cmd))
		{
			ft_putstr_fd("export : not an identifier", 2);
			sh->exit_code = 1;
			return (0);
		}
	}
	return (1);
}

int	handle_export(t_sh *sh, char **value, int *equal_pos, char **var)
{
	*value = ft_strchr(sh->ptr_cmd->cmd, '=');
	if (!*value)
	{
		if (sh->ptr_cmd->next && ft_strchr(sh->ptr_cmd->next, '='))
		{
			errno = UNV_ID;
			error(sh, ((t_lst_cmd *)sh->ptr_cmd->next)->cmd);
			sh->exit_code = 1;
			exit_code(sh, errno);
			return (0);
		}
		env_lstaddback(&sh->ptr_env, env_lstnew(sh->ptr_cmd->cmd, ""));
	}
	if (*value)
		*equal_pos = ft_strchr(sh->ptr_cmd->cmd, '=')
			- (char *)sh->ptr_cmd->cmd;
	if (*equal_pos)
		*var = ft_substr(sh->ptr_cmd->cmd, 0, *equal_pos);
	return (1);
}

int	handle_export2(t_sh *sh, char **value, int *equal_pos, char **var)
{
	if (*value)
	{
		if (ft_strlen(sh->ptr_cmd->cmd) > 1)
			*value = ft_substr(sh->ptr_cmd->cmd, *equal_pos + 1,
					ft_strlen(sh->ptr_cmd->cmd));
		else
			*value = ft_substr(sh->ptr_cmd->cmd, *equal_pos,
					ft_strlen(sh->ptr_cmd->cmd));
	}
	if (!ft_strcmp(*value, "="))
	{
		errno = UNV_ID;
		error(sh, *value);
		sh->exit_code = 1;
		exit_code(sh, errno);
		return (0);
	}
	else if (*var && *value && !env_lstdupe(sh, *var, *value))
	{
		sh->ptr_env = sh->lst_env;
		env_lstaddback(&sh->ptr_env, env_lstnew(*var, *value));
		errno = 0;
	}
	return (1);
}

void	ft_export(t_sh *sh)
{
	char	*value;
	char	*var;
	int		equal_pos;

	value = NULL;
	var = NULL;
	equal_pos = 0;
	errno = 0;
	sh->ptr_cmd = sh->lst_cmd;
	while (sh->ptr_cmd)
	{
		if (!solo_export(sh, equal_pos, value))
			return ;
		if (!handle_export(sh, &value, &equal_pos, &var))
			return ;
		if (!handle_export2(sh, &value, &equal_pos, &var))
			return ;
		sh->ptr_cmd = sh->ptr_cmd->next;
		exit_code(sh, errno);
	}
}

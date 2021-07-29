/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 17:47:03 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/29 19:15:41 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void engine_cd(t_sh *sh, int *ret, char *str)
{
	env_lstedit(sh, "OLDPWD", get_actual_path());
	*ret = chdir(env_lstcontent(sh, str));
	env_lstedit(sh, "PWD", get_actual_path());
}

void ft_cd(t_sh *sh)
{
	errno = 0;
	char *tmp;
	
	sh->ptr_cmd = sh->lst_cmd;
	sh->ptr_env = sh->lst_env;
	
	if (!env_lstfinder(sh->ptr_env, "PWD"))
		tmp = NULL;
	else
		tmp = ft_strdup(env_lstfinder(sh->ptr_env, "PWD")->content);
	if (!sh->ptr_cmd->next || !ft_strcmp(((t_lst_cmd*)sh->ptr_cmd->next)->cmd,"~"))
	{
		engine_cd(sh, &errno, "HOME");
		return;
	}
	sh->ptr_cmd = sh->ptr_cmd->next;
	if (sh->ptr_cmd->next)
	{
		ft_putstr_fd("My Minishell: cd:", 2);
		ft_putstr_fd(" too many arguments\n", 2);
		return ;
	}
	errno = chdir(sh->ptr_cmd->cmd);
	if (errno == -1)
	{
		ft_putstr_fd("My Minishell: cd: ", 2);
		ft_putstr_fd(sh->ptr_cmd->cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}
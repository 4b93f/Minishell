/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 17:47:03 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/11 23:01:53 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

static void	engine_cd(t_sh *sh, int *ret, char *str)
{
	char	*actual_path;

	actual_path = get_actual_path();
	if (!actual_path)
	{
		*ret = chdir("..");
		actual_path = get_actual_path();
		if (env_lstfinder(sh->lst_env, "OLDPWD"))
			env_lstedit(sh, "OLDPWD", actual_path);
		if (env_lstfinder(sh->lst_env, "PWD"))
			env_lstedit(sh, "PWD", actual_path);
		free(actual_path);
		return ;
	}
	if (env_lstfinder(sh->lst_env, "OLDPWD"))
		env_lstedit(sh, "OLDPWD", actual_path);
	else
		env_lstaddback(&sh->lst_env, env_lstnew("OLDPWD", actual_path));
	*ret = chdir(str);
	free(actual_path);
	actual_path = get_actual_path();
	if (env_lstfinder(sh->lst_env, "PWD"))
		env_lstedit(sh, "PWD", actual_path);
	else
		env_lstaddback(&sh->lst_env, env_lstnew("PWD", actual_path));
	free(actual_path);
}

static void	cd_error(t_sh *sh)
{
	ft_putstr_fd("My Minishell: ", 2);
	ft_putendl_fd(strerror(errno), 2);
	sh->exit_code = 1;
}

void	ft_cd(t_sh *sh)
{
	int	ret;

	ret = 0;
	errno = 0;
	sh->ptr_cmd = sh->lst_cmd;
	sh->ptr_env = sh->lst_env;
	if (!sh->ptr_cmd->next || !ft_strcmp(((t_lst_cmd *)sh->ptr_cmd->next)->cmd,
			"~"))
	{
		engine_cd(sh, &errno, env_lstcontent(sh, "HOME"));
		return ;
	}
	sh->ptr_cmd = sh->ptr_cmd->next;
	if (sh->ptr_cmd->next && ft_strcmp(((t_lst_cmd *)sh->ptr_cmd->next)->cmd,
			"|"))
	{
		ft_putstr_fd("My Minishell: cd:", 2);
		ft_putstr_fd(" too many arguments\n", 2);
		sh->exit_code = 1;
		return ;
	}
	engine_cd(sh, &ret, sh->ptr_cmd->cmd);
	if (ret == -1)
		cd_error(sh);
	exit_code(sh, 0);
}

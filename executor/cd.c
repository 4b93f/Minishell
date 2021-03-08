/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:03:53 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/08 13:15:33 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include "executor.h"

void	ft_cd(t_cmd_lst *cmd, t_sh *sh)
{
	// struct stat	buffer;
	char		*ptr;
	int			ret;
	char		*tmp;

	ret = 0;
	errno = 0;
	ptr = NULL;
	if (env_lst_finder(sh->env_lst, "HOME"))
	{
		if (!(env_lst_finder(sh->env_lst, "OLDPWD")))
			ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(ft_strdup("OLDPWD"), NULL));
	}
	if (!env_lst_finder(sh->env_lst, "PWD"))
		tmp = NULL;
	else
		tmp = ft_strdup(env_lst_finder(sh->env_lst, "PWD")->content);
	if (cmd->str && cmd->str->content)
		ptr = ft_is_var(cmd->str->content, sh);
	if (!ptr && cmd->str && cmd->str)//----------------------------IF $VAR NOT SET RETURN ERROR----------------
	{
		ft_putstr_fd("minishell: cd: ", cmd->fd_pipe_out);
		ft_putstr_fd(cmd->str->content, cmd->fd_pipe_out);
		ft_putstr_fd(" not set\n", cmd->fd_pipe_out);
		free(tmp);
		return ;
	}
	//if ((ret = stat(ptr, &buffer)) == -1)
	//{
	//	free(ptr);	
	//	free(tmp);	
	//	ft_error(0, sh, 0);
	//}
	if (ptr) 
		ret = chdir(ptr);
	free(ptr);
	if (ret == 0)
	{
		if (!cmd->str)
		{
			if (!env_lst_finder(sh->env_lst, "HOME"))
				ft_putstr_fd("minishell: cd: HOME not set\n", cmd->fd_pipe_out);
			else
				chdir(env_lst_finder(sh->env_lst, "HOME")->content);
		}
		if (!env_lst_finder(sh->env_lst, "PWD"))
			ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(ft_strdup("PWD"), NULL));
		ft_set_free_env(sh, "PWD", get_actual_path());
	}
	else if (cmd->str && ft_strlen(cmd->str->content = rm_guim(cmd->str->content)))
	{
		ft_putstr_fd("minishell: cd: ", cmd->fd_pipe_out);
		ft_putstr_fd(cmd->str->content, cmd->fd_pipe_out);
		if (errno == PERM_DENIED)
			ft_putstr_fd(": Permission denied\n", cmd->fd_pipe_out);
		else
			ft_putstr_fd(": No such file or directory\n", cmd->fd_pipe_out);
		free(tmp);
		return ;
	}
	if (cmd->str || env_lst_finder(sh->env_lst, "HOME"))
	{
		ft_set_free_env(sh, "OLDPWD", tmp);
		ft_set_free_env(sh, "?", ft_itoa(0));
	}
}

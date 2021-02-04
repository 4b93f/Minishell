/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 01:19:10 by jsilance          #+#    #+#             */
/*   Updated: 2021/02/04 02:47:32 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	/!\ gerer si plus que flag et arg.
**	/!\ gerer erreur de guillemet + trim.
*/

static void	ft_echo(t_cmd_lst *cmd, t_sh *sh)
{
	t_list	*ptr_lst;
	char	*ptr;

	ptr_lst = cmd->str;
	if (!ptr_lst && !(cmd->flags && !ft_strcmp("-n", cmd->flags)))
		write(cmd->fd_pipe_out, "\n", 1);
	while (ptr_lst)
	{
		ptr_lst->content = rm_guim(ptr_lst->content);
		ptr = ft_is_var(ptr_lst->content, sh);
		ft_putstr_fd(ptr, cmd->fd_pipe_out);
		free(ptr);
		ptr_lst = ptr_lst->next;
		if (ptr_lst)
			write(cmd->fd_pipe_out, " ", 1);
		else if (!(cmd->flags && !ft_strncmp("-n", cmd->flags, 2)))
			write(cmd->fd_pipe_out, "\n", 1);
	}
	free(env_lst_finder(sh->env_lst, "?")->content);
	ptr = ft_itoa(0);
	env_lst_finder(sh->env_lst, "?")->content = ft_strdup(ptr);
	free(ptr);
}

/*
**	voir si besoin de gere le old pwd dans l'env.
**	adapter avec l'ancien ft_cd.
*/

static void	ft_cd(t_cmd_lst *cmd, t_sh *sh)
{
	t_env_lst	*env;
	char		*ptr;
	int			ret;

	if (!(env_lst_finder(sh->env_lst, "OLDPWD")))
		ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew("OLDPWD", NULL));
	env = env_lst_finder(sh->env_lst, "OLDPWD");
	free(env->content);
	env->content = NULL;
	ptr = get_actual_path();
	env->content = ft_strdup(ptr);
	if (env->content)
		return ;
	free(ptr);
	ptr = ft_is_var(cmd->str->content, sh);
	ret = chdir(ptr);
	free(ptr);
	if (!ret)
	{
		env = env_lst_finder(sh->env_lst, "PWD");
		free(env->content);
		ptr = get_actual_path();
		env->content = ft_strdup(ptr);
		free(ptr);
	}
	free(env_lst_finder(sh->env_lst, "?")->content);
	ptr = ft_itoa(ret);
	env_lst_finder(sh->env_lst, "?")->content = ft_strdup(ptr);
	free(ptr);
}

static void	commander_exec(t_cmd_lst *cmd, t_sh *sh)
{
	if (cmd->cmd_index == -1)
		exec_cmd(cmd, sh);
	else if (cmd->cmd_index == 0)
		ft_exit(cmd, sh);
	else if (cmd->cmd_index == 1)
		ft_echo(cmd, sh);
	else if (cmd->cmd_index == 2)
		ft_cd(cmd, sh);
	else if (cmd->cmd_index == 3)
		ft_pwd(cmd);
	else if (cmd->cmd_index == 4)
		ft_export(cmd, sh);
	else if (cmd->cmd_index == 5)
		ft_unset(cmd, sh);
	else if (cmd->cmd_index == 6)
		print_env(sh->env_lst, cmd->fd_pipe_out);
}

static void	fork_piper(t_cmd_lst *ptr_cmd, t_sh *sh)
{
	int	pid;
	t_cmd_lst	*ccmd;

	ccmd = ptr_cmd->next;
	pid = fork();
	if (pid)
	{
		close(ccmd->fd_pipe_out);
		ptr_cmd = ptr_cmd->next;
		ptr_cmd->pid = pid;
	}
	else
	{
		ptr_cmd->pid = pid;
		close(ptr_cmd->fd_pipe_in);
	}
	commander_exec(ptr_cmd, sh);
	if (!pid)
	{	
		close(ccmd->fd_pipe_in);
		exit(0);
	}
	close(ccmd->fd_pipe_out);
	kill(pid, SIGQUIT);
}

int		executor(t_sh *sh)
{
	t_cmd_lst	*ptr_cmd;

	ptr_cmd = sh->cmd;
	while (ptr_cmd)
	{
		if (ptr_cmd->pipe_out && ptr_cmd->next)
		{
			fork_piper(ptr_cmd, sh);
			if (ptr_cmd->fd_pipe_out)
				ptr_cmd = ptr_cmd->next;
		}
		else
			commander_exec(ptr_cmd, sh);
		ptr_cmd = ptr_cmd->next;
	}
	return (0);
}

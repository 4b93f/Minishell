/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 01:19:10 by jsilance          #+#    #+#             */
/*   Updated: 2021/02/16 19:31:554 by chly-huc         ###   ########.fr       */
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
		//printf("!\n");
		//printf("{%s}\n", ptr_lst->content);
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
	ft_set_free_env(sh, "?", ft_itoa(0));
}

void	ft_set_free_env(t_sh *sh, void *var, void *content)
{
	t_env_lst	*ptr;

	if (!sh)
		return ;
	ptr = env_lst_finder(sh->env_lst, var);
	if (!ptr)
		ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(ft_strdup(var), content));
	else
	{
		if (ptr->content)
			free(ptr->content);
		ptr->content = content;
	}
}	

/*
**	voir si besoin de gere le old pwd dans l'env.
**	adapter avec l'ancien ft_cd.
*/

static void	ft_cd(t_cmd_lst *cmd, t_sh *sh)
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
		//printf("!\n");
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

static void	commander_exec(t_cmd_lst *cmd, t_sh *sh)
{
	if (cmd->str)
		ft_set_free_env(sh, "_", ft_strdup(ft_lstlast(cmd->str)->content));
	else
		ft_set_free_env(sh, "_", ft_strjoin(ft_search_path(sh, cmd), cmd->cmd_str));
	if (cmd->cmd_index == -1)
		exec_cmd(cmd, sh);
	else if (cmd->cmd_index == 0)
		ft_exit(cmd, sh);
	else if (cmd->cmd_index == 1)
		ft_echo(cmd, sh);
	else if (cmd->cmd_index == 2)
		ft_cd(cmd, sh);
	else if (cmd->cmd_index == 3)
		ft_pwd(cmd, sh);
	else if (cmd->cmd_index == 4)
		ft_export(cmd, sh);
	else if (cmd->cmd_index == 5)
		ft_unset(cmd, sh);
	else if (cmd->cmd_index == 6)
		print_env(sh->env_lst, cmd->fd_pipe_out, sh);
}

static void	fork_piper(t_cmd_lst *ptr_cmd, t_sh *sh)
{
	int			pid;
	t_cmd_lst	*ccmd;
	int			fd_backup[2];

	fd_backup[0] = dup(0);
	fd_backup[1] = dup(1);
	ccmd = ptr_cmd->next;
	dup2(ptr_cmd->fd_pipe_out, 1);
	dup2(ccmd->fd_pipe_in, 0);
	pid = fork();
	if (pid)
	{
		close(ptr_cmd->fd_pipe_out);
		ptr_cmd = ptr_cmd->next;
		ptr_cmd->pid = pid;
		dup2(fd_backup[1], 1);
		dup2(ptr_cmd->fd_pipe_in, 0);
	}
	else
	{
		close(ccmd->fd_pipe_in);
		ptr_cmd->pid = pid;
	}
	wait(0);
	commander_exec(ptr_cmd, sh);
	if (!pid)
	{
		if (ptr_cmd->fd_pipe_out > 2)
			close(ptr_cmd->fd_pipe_out);
		exit(0);
	}
// printf("", );
	close(ptr_cmd->fd_pipe_in);
	dup2(fd_backup[0], 0);
	kill(pid, SIGQUIT);
}

int		executor(t_sh *sh)
{
	t_cmd_lst	*ptr_cmd;
	char		*buf;

	buf = NULL;
	ptr_cmd = sh->cmd;
	while (ptr_cmd)
	{
		if (ptr_cmd->pipe_out == 2) // commande pour '>'
			if ((ptr_cmd->fd_pipe_out = open(ptr_cmd->red_file->content, O_CREAT | O_WRONLY | O_TRUNC, 0777)) < 0)
				ft_error(0, sh, 1); // --------****A CORRIGER****----------
		if (ptr_cmd->pipe_out == 3) // commande pour '>>'
			if ((ptr_cmd->fd_pipe_out = open(ptr_cmd->red_file->content, O_CREAT | O_APPEND | O_WRONLY, 0777)) < 0)
				ft_error(0, sh, 1); // --------****A CORRIGER****----------
		if (ptr_cmd->pipe_out == 4) // commande pour '<'
			if ((ptr_cmd->fd_pipe_in = open(ptr_cmd->red_file->content, O_APPEND | O_RDONLY, 0777)) < 0)
				ft_error(0, sh, 1); // --------****A CORRIGER****----------
		if (ptr_cmd->pipe_out == 1 && ptr_cmd->next)
		{
			fork_piper(ptr_cmd, sh);
			if (ptr_cmd->fd_pipe_out > 2)
				close(ptr_cmd->fd_pipe_out);	
			if (ptr_cmd->fd_pipe_out && ptr_cmd->next)
				ptr_cmd = ptr_cmd->next;
		}
		else
		{	
			commander_exec(ptr_cmd, sh);
			if (ptr_cmd->fd_pipe_out > 2)
				close(ptr_cmd->fd_pipe_out);
		}
		ptr_cmd = ptr_cmd->next;
	}
	return (0);
}

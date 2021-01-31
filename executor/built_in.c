/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 13:33:07 by chly-huc          #+#    #+#             */
/*   Updated: 2021/01/31 05:26:44 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_cmd_lst *cmd)
{
    char *buf;

    buf = get_actual_path();
	ft_putstr_fd(buf, cmd->fd_pipe_out);
	if (!cmd->pipe_out)
		ft_putstr_fd("\n", cmd->fd_pipe_out);
	free(buf);
}

/*
void ft_cd(t_sh *sh)
{
	struct stat buffer;
	char *path;
	int i;
	
	i = 0;
	path = NULL;
	// free(sh->old_pwd);
	// sh->old_pwd = get_actual_path(); 
	// if (!strcmp("cd /", sh->input_str))
		// chdir("/");
	if (!strcmp("cd ~", sh->input_str) || !strcmp("cd", sh->input_str))
	{
		while(strncmp(sh->env[i], "HOME=", ft_strlen("HOME=")))
			i++;
		chdir(sh->env[i] + ft_strlen("HOME="));
	}
	i = stat("/Users/chly-huc/Desktop/minish", &buffer);
	path = get_actual_path();
	path = ft_strjoinfree(path, "/");
	path = ft_strjoinfree(path, sh->input_str + ft_strlen("cd "));
	if (i == -1)
		return ;
	else
	{
		if (S_ISDIR(buffer.st_mode))
			chdir(path);
	}
	free(sh->actual_pwd);
	sh->actual_pwd = get_actual_path();
	free(path);
}
*/

char	**lst_db_tab(t_cmd_lst *cmd)
{
	char	**ptr;
	t_list	*arg_ptr;
	int		size;

	ptr = NULL;
	size = ft_lstsize(cmd->str);
	arg_ptr = cmd->str;
	if (!(ptr = ft_calloc(sizeof(char *), size + 2)))
		return (NULL);
	size = -1;
	if (!(ptr[++size] = ft_strdup(cmd->cmd_str)))
	{
		free_tab(ptr);
		return (NULL);
	}
	while(arg_ptr)
	{
		if (!(ptr[++size] = ft_strdup(arg_ptr->content)))
		{
			free_tab(ptr);
			return (NULL);
		}
		arg_ptr = arg_ptr->next;
	}
	return (ptr);
}

/*
**	/!\ s'occuper des pipes via dup2 --> /!\ STDIN PROBLEMES.
**	/!\ remplacer "/bin/" par une variable all_path
**	
*/

void	exec_cmd(t_cmd_lst *cmd, t_sh *sh)
{
	pid_t	child_pid;
	pid_t	dad_pid;
	char	**tmp;
	char	*ptr;
	char	*sf;
	int		io[2];

	io[0] = dup(STDIN_FILENO);
	io[1] = dup(STDOUT_FILENO);
	sf = ft_search_path(sh, cmd);
	ptr = ft_strjoin(sf, cmd->cmd_str);
	free(sf);
	tmp = lst_db_tab(cmd);
	child_pid = fork();
	if (!child_pid)
	{
		dup2(cmd->fd_pipe_out, STDOUT_FILENO);
		dup2(cmd->fd_pipe_in, STDIN_FILENO);
		if (execve(ptr, tmp, NULL) == -1);
			ft_putstr_fd("Command not found!\n", cmd->fd_pipe_out);
		exit(0);
	}
	else
		dad_pid = wait(0);
	dup2(STDIN_FILENO, io[0]);
	dup2(STDOUT_FILENO, io[1]);
	free(ptr);
	free_tab(tmp);
}

void	ft_export(t_cmd_lst *cmd, t_sh *sh)
{
	int			equal_pos;
	char		*var;
	char		*value;
	t_env_lst	*chainon;
	t_list		*ptr_str;

	ptr_str = cmd->str;
	chainon = NULL;
	while (ptr_str)
	{
		if (ft_strchr(ptr_str->content, 61))
		{
			equal_pos = ft_strchr(ptr_str->content, 61) - (char *)ptr_str->content;
			var = ft_substr(ptr_str->content, 0, equal_pos);
			value = ft_substr(ptr_str->content, equal_pos + 1, ft_strlen(ptr_str->content));
			chainon = env_lst_finder(sh->env_lst, var);
			if (!chainon)
				ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(var, value));
			else
			{
				free(var);
				free(chainon->content);
				chainon->content = value;
			}
		}
		ptr_str = ptr_str->next;
	}
}

void	ft_unset(t_cmd_lst *cmd, t_sh *sh)
{
	t_list	*ptr_str;

	ptr_str = cmd->str;
	while (ptr_str)
	{
		ft_env_lstdelone(env_lst_finder(sh->env_lst, ptr_str->content), free);
		ptr_str = ptr_str->next;
	}
}

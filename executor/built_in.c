/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 13:33:07 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/16 18:36:444 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_cmd_lst *cmd, t_sh *sh)
{
    char *buf;

    buf = get_actual_path();
	if (!buf)
		return;
	ft_putstr_fd(buf, cmd->fd_pipe_out);
	if (!cmd->pipe_out)
		ft_putstr_fd("\n", cmd->fd_pipe_out);
	free(buf);
	free(env_lst_finder(sh->env_lst, "?")->content);
	env_lst_finder(sh->env_lst, "?")->content = ft_itoa(0);
}

/*
**	Convert string of command in double tab.
*/

char	**lst_db_tab(t_cmd_lst *cmd)
{
	char	**ptr;
	t_list	*arg_ptr;
	int		size;

	ptr = NULL;
	size = ft_lstsize(cmd->str);
	arg_ptr = cmd->str;
	ptr = ft_calloc(sizeof(char *), size + 2);
	if (!ptr)
		return (NULL);
	size = -1;
	ptr[++size] = ft_strdup(cmd->cmd_str);
	if (!ptr)
		return (free_tab(ptr));
	while(arg_ptr)
	{
		arg_ptr->content = rm_guim(arg_ptr->content);
		ptr[++size] = ft_strdup(arg_ptr->content);
		if (!ptr)
			return (free_tab(ptr));
		arg_ptr = arg_ptr->next;
	}
	return (ptr);
}

static char	**ft_lst_to_tab(t_env_lst *lst)
{
	char		**ptr;
	t_env_lst	*arg_ptr;
	int			size;

	ptr = NULL;
	size = ft_env_lstsize(lst);
	arg_ptr = lst;
	ptr = ft_calloc(sizeof(char *), size + 1);
	if (!ptr)
		return (NULL);
	size = -1;
	while(arg_ptr)
	{
		ptr[++size] = ft_strdup(arg_ptr->var);
		if (!ptr)
			return (free_tab(ptr));
		arg_ptr = arg_ptr->next;
	}
	return (ptr);
}

static void	ft_not_found(t_cmd_lst *cmd, t_sh *sh, int pid, int fd[2])
{
	ft_putstr_fd("minishell: ", cmd->fd_pipe_out);
	ft_putstr_fd(cmd->cmd_str, cmd->fd_pipe_out);
	ft_putstr_fd(": command not found\n", cmd->fd_pipe_out);
	ft_portal(sh, 127, pid, fd);
	// printf("Send value [127]\n");
}

void	exec_cmd(t_cmd_lst *cmd, t_sh *sh)
{
	pid_t	child_pid;
	char	**tmp;
	char	**tmpenv;
	char	*ptr;
	char	*sf;
	int		portal[2];

	sf = ft_search_path(sh, cmd);
	ptr = ft_strjoin(sf, cmd->cmd_str);
	if (!ptr)
		return;
	tmp = lst_db_tab(cmd);
	tmpenv = lst_db_tab(sh->env_lst);
	if (pipe(portal) < 0)
		ft_error(PIPE_ERROR, sh, 0);
	child_pid = fork();
	if (!child_pid)
	{
		if (execve(ptr, tmp, tmpenv) == -1)
		{
			printf("!\n");
			//printf("1\n");
			ft_not_found(cmd, sh, child_pid, portal);
		}
		else
		{
			//printf("2\n");
			ft_portal(sh, 0, child_pid, portal);
		}
		//printf("3\n");
		exit(0);
	}
// printf("[%s][%d][%d]\n", cmd->cmd_str, cmd->fd_pipe_in, cmd->fd_pipe_out);
// printf("[%s][%d][%d]\n", cmd->cmd_str, cmd->fd_pipe_in, cmd->fd_pipe_out);
	wait(0);
// printf("[***]\n");
	ft_portal(sh, 0, child_pid, portal);
	free(ptr);
	free(tmpenv);
	free_tab(tmp);
}

/*
**	si la string est bien alphanumerique le result sera NULL.
**	sinon le char en question sera renvoye.
*/

static char	*ft_str_isalnum(char *str)
{
	while (str && *str)
	{
		if (!ft_isalnum(*str) && *str != '_' && *str != '\\')
			return (--str);
		str++;
	}
	return (NULL);
}

void	ft_sort_export(t_sh *sh, t_cmd_lst *cmd)
{
	char		*tmp;
	char		**tab;
	int			size;
	int			i;
	int			j;

	i = -1;
	size = ft_env_lstsize(sh->env_lst);
	tab = ft_lst_to_tab(sh->env_lst);
	if (!tab)
		return ;
	while (++i < size)
	{
		j = i;
		while (++j < size)
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
	}
	i = -1;
	while (tab && tab[++i])
	{
		if (!ft_strcmp(tab[i], "?") || !ft_strcmp(tab[i], "_"))
			continue ;
		ft_putstr_fd("declare -x ", cmd->fd_pipe_out);
		ft_putstr_fd(env_lst_finder(sh->env_lst, tab[i])->var, cmd->fd_pipe_out);
		ft_putstr_fd("=\"", cmd->fd_pipe_out);
		ft_putstr_fd(env_lst_finder(sh->env_lst, tab[i])->content, cmd->fd_pipe_out);
		ft_putstr_fd("\"\n", cmd->fd_pipe_out);
	}
	free_tab(tab);
}

void	ft_export(t_cmd_lst *cmd, t_sh *sh)
{
	int			equal_pos;
	char		*var;
	char		*value;
	t_env_lst	*chainon;
	t_list		*ptr_str;

	ptr_str = cmd->str;
	if (!ptr_str)
	{
		ft_sort_export(sh, cmd);
		return ;
	}
	while (ptr_str)
	{
		equal_pos = ft_strchr(ptr_str->content, 61) - (char *)ptr_str->content;
		var = ft_substr(ptr_str->content, 0, equal_pos - 1);
		if (!var)
			return;
		if (equal_pos == 1)
		{
			ft_putstr_fd("minishell: export: `", cmd->fd_pipe_out);
			ft_putstr_fd(ptr_str->content, cmd->fd_pipe_out);
			ft_putstr_fd("': not a valid identifier\n", cmd->fd_pipe_out);
			free(env_lst_finder(sh->env_lst, "?")->content);
			env_lst_finder(sh->env_lst, "?")->content = ft_strdup("1");
		}
		var = rm_guim(var);
		if (ft_str_isalnum(var))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token '", cmd->fd_pipe_out);
			write(cmd->fd_pipe_out, ft_str_isalnum(var), 1);
			write(cmd->fd_pipe_out, "'\n", 2);
			free(env_lst_finder(sh->env_lst, "?")->content);
			env_lst_finder(sh->env_lst, "?")->content = ft_itoa(2);
			free(var);
			return ;
		}
		ptr_str = ptr_str->next;
		free(var);
	}
	ptr_str = cmd->str;
	chainon = NULL;
	while (ptr_str)
	{
		if (ft_strchr(ptr_str->content, 61))
		{
			equal_pos = ft_strchr(ptr_str->content, 61) - (char *)ptr_str->content;
			var = ft_substr(ptr_str->content, 0, equal_pos - 1);
			value = ft_substr(ptr_str->content, equal_pos, ft_strlen(ptr_str->content));
		// printf("[%s]\n", value);
			chainon = env_lst_finder(sh->env_lst, var);
			if (!chainon)
				ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(var, value));
			else
			{
				free(var);
				if (chainon)
				{	
					free(chainon->content);
					chainon->content = value;
				}
			}
		}
		ptr_str = ptr_str->next;
	}
	free(env_lst_finder(sh->env_lst, "?")->content);
	env_lst_finder(sh->env_lst, "?")->content = ft_itoa(0);
}

void	ft_unset(t_cmd_lst *cmd, t_sh *sh)
{
	t_list	*ptr_str;
	int		equal_pos;

	ptr_str = cmd->str;
	while (ptr_str)
	{
		equal_pos = 0;
		ptr_str->content = rm_guim(ptr_str->content);
		equal_pos = (ft_strchr(ptr_str->content, '=') || ft_strchr(ptr_str->content, ' '));
		if (equal_pos)
		{
			ft_putstr_fd("minishell: unset: `", cmd->fd_pipe_out);
			ft_putstr_fd(ptr_str->content, cmd->fd_pipe_out);
			ft_putstr_fd("': not a valid identifier\n", cmd->fd_pipe_out);
			free(env_lst_finder(sh->env_lst, "?")->content);
			env_lst_finder(sh->env_lst, "?")->content = ft_strdup("0");
		}
		else if (ft_str_isalnum(ptr_str->content))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token '", cmd->fd_pipe_out);
			write(cmd->fd_pipe_out, ft_str_isalnum(ptr_str->content), 1);
			write(cmd->fd_pipe_out, "'\n", 2);
			free(env_lst_finder(sh->env_lst, "?")->content);
			env_lst_finder(sh->env_lst, "?")->content = ft_strdup("2");
		}
		ptr_str = ptr_str->next;
	}
	ptr_str = cmd->str;
	while (ptr_str)
	{
		ft_env_lstdelone(env_lst_finder(sh->env_lst, ptr_str->content), free);
		ptr_str = ptr_str->next;
	}
	free(env_lst_finder(sh->env_lst, "?")->content);
	env_lst_finder(sh->env_lst, "?")->content = ft_itoa(0);
}

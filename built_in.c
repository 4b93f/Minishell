/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 13:33:07 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/02 02:51:26 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_cmd_lst *cmd)
{
    char *buf;
	int size;
	
	size = 40000;
	buf = NULL;
	
    buf = getcwd(buf, size);
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

void	exec_cmd(t_cmd_lst *cmd, t_sh *sh)
{
	pid_t	child_pid;
	pid_t	dad_pid;
	char	**tmp;
	char	*ptr;

	ptr = ft_strjoin("/bin/", cmd->cmd_str);
	tmp = lst_db_tab(cmd);
	child_pid = fork();
	if (!child_pid)
		execve(ptr, tmp, NULL);
	else
		dad_pid = wait(0);
	free(ptr);
	free_tab(tmp);
	if (!child_pid)
		exit(0);
}

/*
int  sort_export(t_sh *sh, int i, int j, int len)
{
	char *tmp;
	char **ok;
	int modif;
	
	modif = 0;
	i = -1;
	ok = tabcpy(sh->env);
	while(modif == 0)
	{
		i = 0;
		modif = 1;
		while (i < len - 1)
		{
			if (ok[i] && strcmp(ok[i], ok[i + 1]) > 0)
			{
				tmp = ok[i];
				ok[i] = ok[i + 1];
				ok[i + 1] = tmp;
				modif = 0;
			}
			i++;
		}
		len--;
	}
	print_tab(ok);
	free_tab(ok);
	return (0);
}
*/


void	ft_export(t_cmd_lst *cmd, t_sh *sh)
{
	int		equal_pos;
	char	*var;
	char	*value;
	t_list	*ptr_str;

	ptr_str = cmd->str;
	while (ptr_str)
	{
		equal_pos = ft_strchr(ptr_str->content, 61) - (char *)ptr_str->content;
		var = ft_substr(ptr_str->content, 0, equal_pos);
		value = ft_substr(ptr_str->content, equal_pos + 1, ft_strlen(ptr_str->content));
		ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(var, value));
		ptr_str = ptr_str->next;
	}
}

/*
void ft_export(t_sh *sh)
{
	int i;
	int j;
	int k;
	char **tab;

	i = 0;
	j = 0;
	k = 0;
	tab = NULL;
	if (!(tab = ft_split(sh->input_str, ' ')))
		return;
	if (!strcmp(sh->input_str, "export"))
		sort_export(sh, 0, 0, tablen(sh->env));
	while (tab[++k])
	{
		if (ft_strchr(tab[k], '='))
		{
			j = 0;
			i = 0;
			while (tab[k][i] && tab[k][i] != '=')
				i++;
			while (sh->env[j] && tab[k] && ft_strncmp(sh->env[j], tab[k], i))
				j++;
			if (!sh->env[j])
				create_env(sh, tab[k]);
			else
			{
				if (ft_strchr(tab[k], '='))
				{
					free(sh->env[j]);
					sh->env[j] = ft_strdup(tab[k]);
				}
			}
		}
	}
	free_tab(tab);
}
*/

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

/*
void ft_unset(t_sh *sh)
{
	int i;
	int j;
	int len;
	char **tab;
	
	i = 0;
	j = 0;
	if (!(tab = ft_split(sh->input_str, ' ')))
		return ;
	while (tab[++i])
	{
		j = 0;
		while (sh->env[j] && ft_strncmp(sh->env[j], tab[i], ft_strlen(tab[i])))
			j++;
		if (!sh->env[j])
		{
			free_tab(tab);
			return ;
		}
		else
		{
			len = tablen(sh->env);
			sh->env = delete_env(sh, tab[i], len);
		}
	}
	free_tab(tab);
}
*/
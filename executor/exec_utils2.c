/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:02:44 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/08 13:15:59 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include "executor.h"

/*
**	si la string est bien alphanumerique le result sera NULL.
**	sinon le char en question sera renvoye.
*/

char	*ft_str_isalnum(char *str)
{
	while (str && *str)
	{
		if (!ft_isalnum(*str) && *str != '_' && *str != '\\')
			return (str);
		str++;
	}
	return (NULL);
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

char	**ft_lst_to_tab(t_env_lst *lst)
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

char	**envlst_to_tab(t_env_lst *lst)
{
	char		**ptr;
	t_env_lst	*arg_ptr;
	char		*tmp1;
	int			size;

	ptr = NULL;
	if (!lst)
		return (NULL);
	size = ft_env_lstsize(lst);
	arg_ptr = lst;
	ptr = ft_calloc(sizeof(char *), size + 1);
	if (!ptr)
		return (NULL);
	size = 0;
	if (!ptr)
		return (free_tab(ptr));
	
	while(arg_ptr)
	{
		tmp1 = ft_strjoin(arg_ptr->var, "=");
		ptr[size++] = ft_strjoin(tmp1, arg_ptr->content);
		free(tmp1);
		if (!ptr)
			return (free_tab(ptr));
		arg_ptr = arg_ptr->next;
	}
	return (ptr);
}

void	print_declare(t_sh *sh, t_cmd_lst *cmd, char **tab, int i)
{
	int		j;
	char	*ptr;

	j = 0;
	ptr = (char *)env_lst_finder(sh->env_lst, tab[i])->content;
	ft_putstr_fd("declare -x ", cmd->fd_pipe_out);
	ft_putstr_fd(env_lst_finder(sh->env_lst, tab[i])->var, cmd->fd_pipe_out);
	ft_putstr_fd("=\"", cmd->fd_pipe_out);
	while (ptr && ptr[j])
	{
		if (ft_strchr("\"$\\", ptr[j]))
			ft_putchar_fd('\\', cmd->fd_pipe_out);
		ft_putchar_fd(ptr[j++], cmd->fd_pipe_out);
	}
	ft_putstr_fd("\"\n", cmd->fd_pipe_out);
}

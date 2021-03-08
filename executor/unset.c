/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:59:02 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/08 13:16:37 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include "executor.h"

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

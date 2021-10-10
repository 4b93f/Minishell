/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:31:05 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/10 17:36:39 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void	verif_red_order(t_sh *sh, t_lst_cmd *tmp, int i)
{
	get_type(sh);
	i = get_redir_number(sh);
	i *= 2;
	while (tmp && i > 0)
	{
		if (tmp->type == RIGHT || tmp->type == DRIGHT || tmp->type == LEFT
			|| tmp->type == DLEFT || tmp->redirected == 1)
		{
			go_end(sh, tmp);
			i--;
		}
		tmp = tmp->next;
	}
	tmp = sh->lst_cmd;
	sh->lst_cmd = new_lst(sh);
	cmd_lstclear(&tmp, free);
}

int	verif_syntax(t_sh *sh)
{
	t_lst_cmd	*prev;
	t_lst_cmd	*tmp;

	sh->ptr_cmd = sh->lst_cmd;
	if (sh->ptr_cmd)
		if (!ft_strcmp(sh->ptr_cmd->cmd, "|")
			|| !ft_strcmp(sh->ptr_cmd->cmd, "<")
			|| !ft_strcmp(sh->ptr_cmd->cmd, "<<")
			|| !ft_strcmp(sh->ptr_cmd->cmd, ">")
			|| !ft_strcmp(sh->ptr_cmd->cmd, ">>"))
			return (2);
	prev = sh->lst_cmd;
	tmp = sh->lst_cmd;
	verif_red_order(sh, tmp, 0);
	return (0);
}

void	engine(t_sh *sh)
{
	sh->ptr_cmd = sh->lst_cmd;
	exec(sh, sh->lst_cmd);
	sh_free(sh);
	waitpid(-1, &sh->child_pid, 0);
	if (WIFEXITED(sh->child_pid))
		sh->child_pid = WEXITSTATUS(sh->child_pid);
	if (sh->stat == 1)
		exit(sh->exit_code);
	else if (sh->stat == 2)
		exit_code(sh, sh->child_pid);
	else
		exit_code(sh, sh->exit_code);
	sh->stat = 0;
	sh->ret = 0;
	sh->child_pid = 0;
}

void	setup_engine(t_sh *sh)
{
	str_tolst(sh->input_str, sh, 0, 0);
	quoting(sh);
	if (!sh->lst_cmd)
		return ;
	if (!verif_syntax(sh))
		engine(sh);
	else
	{
		sh_free(sh);
		exit_code(sh, 2);
	}
}

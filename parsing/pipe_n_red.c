/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 14:24:58 by chly-huc          #+#    #+#             */
/*   Updated: 2021/08/04 21:13:52 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

t_lst_cmd *next_sep(t_lst_cmd *ptr_cmd)
{
	while (!str_sep(ptr_cmd->cmd))
		ptr_cmd = ptr_cmd->next;
	if (str_sep(ptr_cmd->cmd) && ptr_cmd->next)
		return(ptr_cmd->next);
	return (NULL);
}

void pipe_engine(t_sh *sh)
{
	int piped[2];

	pipe(piped);
	sh->child_pid = fork();
	if (!sh->child_pid)
	{
		sh->ptr_cmd = sh->lst_cmd;
		
		dup2(piped[1], 1);
		sh->fd_out = piped[1];
		start(sh);
		exit(0);
	}
	else
	{
		close(piped[1]);
		wait(&sh->child_pid);
		dup2(piped[0], 0);
		sh->lst_cmd = next_sep(sh->lst_cmd);
		printf("{%s}\n", sh->lst_cmd->cmd);
	}
}

void pipe_tab(t_sh *sh)
{
	int len = 0;
	int i;
	
	i = -1;
	while(sh->input_str[++i])
		if (sh->input_str[i] == '|')
			len++;
	sh->fd_pipe = malloc(sizeof(int **) * len);
	i = -1;
	while (sh->fd_pipe[++i])
		sh->fd_pipe[i] = malloc(sizeof(int*) * 2);
	sh->fd_pipe[i] = NULL;
}

void pipe_n_red(t_sh *sh)
{



	errno = 0;
	sh->ptr_cmd = sh->lst_cmd;
	pipe_tab(sh);
	
	while (sh->ptr_cmd)
	{	
		if (!sh->ptr_cmd->next)
			return;
		sh->ptr_cmd = sh->ptr_cmd->next;
		if (!ft_strcmp(sh->ptr_cmd->cmd, ">"))
		{
			if (!sh->ptr_cmd->next)
			{
				ft_putstr_fd("My Minishell: syntax error near unexpected token `newline'", 1);
				return ;
			}
			sh->ptr_cmd = sh->ptr_cmd->next;
			sh->fd_out = open(sh->ptr_cmd->cmd, O_CREAT | O_RDWR | O_TRUNC, 0777);
			if (error(sh->ptr_cmd->cmd, errno))
				return;
		}
		if (!ft_strcmp(sh->ptr_cmd->cmd, ">>"))
		{
			if (!sh->ptr_cmd->next)
			{
				ft_putstr_fd("My Minishell: syntax error near unexpected token `newline'", 2);
				return ;
			}
			sh->ptr_cmd = sh->ptr_cmd->next;
			sh->fd_out = open(sh->ptr_cmd->cmd, O_RDWR | O_APPEND | O_CREAT , 0777);
			if (error(sh->ptr_cmd->cmd, errno))
				return;
		}
		if (!ft_strcmp(sh->ptr_cmd->cmd, "<"))
		{
			if (!sh->ptr_cmd->next)
			{
				ft_putstr_fd("My Minishell: syntax error near unexpected token `newline'", 2);
				return ;
			}
			sh->ptr_cmd = sh->ptr_cmd->next;
			sh->fd_out = open(sh->ptr_cmd->cmd, O_RDONLY, 0777);
			if (error(sh->ptr_cmd->cmd, errno))
				return;
		}
		
		if (!ft_strcmp(sh->ptr_cmd->cmd, "|"))
		{
			pipe_engine(sh);
		}
	}
}
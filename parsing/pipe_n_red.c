/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 14:24:58 by chly-huc          #+#    #+#             */
/*   Updated: 2021/08/10 23:31:08 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

t_lst_cmd *next_sep(t_lst_cmd *ptr)
{
	if (!ptr) 
		return (NULL);
	while(ptr)
	{
		if (str_sep(ptr->cmd) && ptr->next)
		{
			return (ptr->next);
		}
		ptr = ptr->next;
	}
	return (NULL);	
}

t_lst_cmd *previous_sep(t_sh *sh, t_lst_cmd *ptr)
{
	t_lst_cmd *parse;
	t_lst_cmd *stock;

	if ((cmd_lstsize(ptr) - cmd_lstsize(sh->lst_cmd)) == 0)
		return (NULL);
	parse = sh->lst_cmd;
	stock = parse;
	while (parse)
	{
		stock = parse;
		parse = next_sep(parse);
		if (ptr == parse)
			return(stock);
		if (parse == NULL)
			return(stock);
	}
	return (NULL);
}

int		ft_pipe(t_sh *sh)
{
	int fd[2];
	int pid;
	if (pipe(fd) == -1)
		strerror(errno);
	if ((pid = fork()) == -1)
		strerror(errno);
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		sh->fd_in = fd[0];
		sh->stat = 1;
		return (2);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		sh->fd_out = fd[1];
		sh->stat = 2;
		return (1);
	}
}

int previous_type(t_sh *sh, t_lst_cmd *ptr)
{
	t_lst_cmd *parse;

	parse = sh->lst_cmd;
	while (parse && parse->next != ptr)
		parse = parse->next;
	if (!parse)
		return(0);
	return (parse->type);
}

void exec(t_sh *sh, t_lst_cmd *token)
{
	int prev_type;
	pid_t pid;	
	t_lst_cmd *next;
	t_lst_cmd *prev;
	
	prev_type = 0;
	pid = 0;
	next = next_sep(token);
	prev = previous_sep(sh, token);
	prev_type = previous_type(sh, token);
	if (sh->block_cmd == 0 && prev && prev_type == PIPE)
		pid = ft_pipe(sh);
	if (sh->block_cmd == 0 && next && pid != 1)
	{
		sh->ptr_cmd = next;
		exec(sh, next);
	}
	if (sh->block_cmd == 0 && (!prev || prev_type == PIPE) && pid != 1)
	{
		sh->ptr_cmd = token;
		start(sh);
	}
}

void pipe_n_red(t_sh *sh)
{
	errno = 0;
	sh->ptr_cmd = sh->lst_cmd;
	
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
			if (error(sh->ptr_cmd->cmd))
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
			if (error(sh->ptr_cmd->cmd))
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
			if (error(sh->ptr_cmd->cmd))
				return;
		}
	
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 14:24:58 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/08 13:47:21 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void	red_forked(t_sh *sh, int pid, char *tmp)
{
	if (sh->fd_in != 0)
		close(sh->fd_out);
	chdir(env_lstcontent(sh, "PWD"));
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &sigret);
		while (ft_strcmp(tmp, sh->ptr_cmd->cmd))
		{
			tmp = readline("> ");
			if (ft_strcmp(tmp, sh->ptr_cmd->cmd))
				ft_putendl_fd(tmp, sh->fd_in);
		}
		exit(0);
	}
	else
	{
		chdir("/tmp");
		close(sh->fd_in);
		sh->fd_in = open("tmp_file", O_CREAT | O_RDWR | O_TRUNC, 00777);
		chdir(env_lstcontent(sh, "PWD"));
		dup2(sh->fd_in, sh->fd_out);
		wait(&pid);
	}
}

t_lst_cmd	*next_sep(t_lst_cmd *ptr)
{
	if (!ptr)
		return (NULL);
	while (ptr)
	{
		if (str_sep(ptr->cmd) && ptr->next)
			return (ptr->next);
		ptr = ptr->next;
	}
	return (NULL);
}

t_lst_cmd	*previous_sep(t_sh *sh, t_lst_cmd *ptr)
{
	t_lst_cmd	*parse;
	t_lst_cmd	*stock;

	if ((cmd_lstsize(ptr) - cmd_lstsize(sh->lst_cmd)) == 0)
		return (NULL);
	parse = sh->lst_cmd;
	stock = parse;
	while (parse)
	{
		stock = parse;
		parse = next_sep(parse);
		if (ptr == parse)
			return (stock);
		if (parse == NULL)
			return (stock);
	}
	return (NULL);
}

int	ft_pipe(t_sh *sh)
{
	int	fd[2];
	int	pid;

	errno = 0;
	if (pipe(fd) == -1)
		printf("OOPSIE\n");
	pid = fork();
	if (!pid)
		return (1);
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		sh->fd_in = fd[0];
		sh->stat = 1;
		return (1);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		sh->fd_out = fd[1];
		sh->stat = 2;
		return (2);
	}
}

int	previous_type(t_sh *sh, t_lst_cmd *ptr)
{
	t_lst_cmd	*parse;

	parse = sh->lst_cmd;
	while (parse && parse->next != ptr)
		parse = parse->next;
	if (!parse)
		return (0);
	return (parse->type);
}

void	check_sep(t_sh *sh, t_lst_cmd *token, t_lst_cmd *prev, int prev_type)
{
	if (sh->block_cmd == 0 && prev && prev_type == RIGHT)
		red_right(sh, token);
	if (sh->block_cmd == 0 && prev && prev_type == DRIGHT)
		red_dright(sh, token);
	if (sh->block_cmd == 0 && prev && prev_type == LEFT)
		red_left(sh, token);
	if (sh->block_cmd == 0 && prev && prev_type == DLEFT)
		red_dleft(sh, token);
}

void	exec(t_sh *sh, t_lst_cmd *token)
{
	int			prev_type;
	pid_t		pid;	
	t_lst_cmd	*next;
	t_lst_cmd	*prev;

	prev_type = 0;
	pid = 0;
	next = next_sep(token);
	prev = previous_sep(sh, token);
	prev_type = previous_type(sh, token);
	check_sep(sh, token, prev, prev_type);
	if (sh->block_cmd == 0 && prev && prev_type == PIPE)
		pid = ft_pipe(sh);
	if (sh->block_cmd == 0 && next && pid != 1)
	{
		sh->ptr_cmd = next;
		exec(sh, next);
	}
	if (sh->block_cmd == 0 && (!prev || prev_type == PIPE) && pid != 2)
	{
		sh->ptr_cmd = token;
		start(sh);
	}
}

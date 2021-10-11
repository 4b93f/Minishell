/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 13:42:33 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/11 21:36:47 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

void	red_forked(t_sh *sh, int pid, char *tmp)
{
	int fd[2];
	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &sigret);
		while (1)
		{
			tmp = readline("> ");
			if (!tmp || !ft_strcmp(tmp, sh->ptr_cmd->cmd))
				break ;
			if (tmp[0] == '$' && env_lstfinder(sh->lst_env, tmp + 1))
			{
				sh->free_ptr = tmp;
				tmp = ft_strdup(env_lstcontent(sh, tmp + 1));
				free(sh->free_ptr);
			}
			write(fd[1], tmp, ft_strlen(tmp));
			write(fd[1], "\n", 1);
			free(tmp);
		}
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	else
	{
		dup2(fd[0], 0);
		wait(&pid);
		close(fd[1]);
	}
}

void	red_right(t_sh *sh, t_lst_cmd *token)
{
	errno = 0;
	sh->ptr_cmd = token;
	if (red_error(sh))
		return ;
	if (sh->fd_out != 1)
		close(sh->fd_out);
	sh->fd_out = open(sh->ptr_cmd->cmd, O_CREAT | O_RDWR | O_TRUNC, 0777);
	dup2(sh->fd_out, 1);
	if (error(sh, sh->ptr_cmd->cmd))
		return ;
}

void	red_dright(t_sh *sh, t_lst_cmd *token)
{
	errno = 0;
	sh->ptr_cmd = token;
	if (red_error(sh))
		return ;
	if (sh->fd_out != 1)
		close(sh->fd_out);
	sh->fd_out = open(sh->ptr_cmd->cmd, O_RDWR
			| O_APPEND | O_CREAT, 0777);
	dup2(sh->fd_out, 1);
	if (error(sh, sh->ptr_cmd->cmd))
		return ;
}

void	red_left(t_sh *sh, t_lst_cmd *token)
{
	errno = 0;
	sh->ptr_cmd = token;
	if (red_error(sh))
		return ;
	if (sh->fd_in != 0)
		close(sh->fd_in);
	sh->fd_in = open(sh->ptr_cmd->cmd, O_RDWR, 0777);
	dup2(sh->fd_in, 0);
	if (errno)
		ft_putendl_fd(strerror(errno), 2);
}

void	red_dleft(t_sh *sh, t_lst_cmd *token)
{
	int		pid;
	char	*tmp;

	errno = 0;
	tmp = NULL;
	pid = 0;
	sh->ptr_cmd = token;
	if (red_error(sh))
		return ;
	if (errno)
		ft_putendl_fd(strerror(errno), 2);
	if (sh->fd_in != 0)
		close(sh->fd_in);
	red_forked(sh, pid, tmp);
}

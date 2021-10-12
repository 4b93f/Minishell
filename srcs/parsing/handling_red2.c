/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_red2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:11:23 by chly-huc          #+#    #+#             */
/*   Updated: 2021/10/12 17:12:43 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

int	heredoc(t_sh *sh, char **tmp, int *fd)
{
	*tmp = readline("> ");
	if (!*tmp || !ft_strcmp(*tmp, sh->ptr_cmd->cmd))
		return (-1);
	if (*tmp[0] == '$' && env_lstfinder(sh->lst_env, *tmp + 1))
	{
		sh->free_ptr = *tmp;
		*tmp = ft_strdup(env_lstcontent(sh, *tmp + 1));
		free(sh->free_ptr);
	}
	write(fd[1], *tmp, ft_strlen(*tmp));
	write(fd[1], "\n", 1);
	return (0);
}

void	red_forked(t_sh *sh, int pid, char *tmp)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &sigret);
		while (1)
		{
			if (heredoc(sh, &tmp, fd) < 0)
				break ;
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

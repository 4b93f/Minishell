/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 15:14:52 by chly-huc          #+#    #+#             */
/*   Updated: 2021/01/30 02:51:22 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	int     pid;
	int     fd[2];
	
	fd[0] = open("./kappa.txt", O_WRONLY);
	// fd[1] = STDOUT_FILENO;
	fd[1] = 1;
	
	pid = fork();
	if (!pid)
	{
		dup2(fd[0], fd[1]);
		execl("./prog", "prog", NULL);
	}
	wait(0);
	return (0);
}
		
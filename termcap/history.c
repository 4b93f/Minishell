/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:01:20 by chly-huc          #+#    #+#             */
/*   Updated: 2021/05/08 17:08:38 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <term.h>
#include <curses.h>
#include <termios.h>
#include <unistd.h>

static int	ft_historysize(t_history *lst)
{
	int i;

	if (!lst)
		return (0);
	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void cmd_history_up(t_sh *sh, t_history *history, int cmd)
{
	int i;
	int j;

	t_history *keep_track_history;
	keep_track_history = history;
	i = -1;
	j = -1;
	if (sh->index_history == -1)
		sh->index_history += 2;
	while (++j < sh->index_history)
		keep_track_history = keep_track_history->next;
	if (history && keep_track_history)
	{
		char *cl = tgetstr("dl", NULL);
		tputs(cl, 1, &ft_putchar);
		char *cl1 = tigetstr("dll");
		tputs(cl1, 1, &ft_putchar);
		write(0, "My Minishell ~> ", 16);
		sh->input_str = ft_strdup(keep_track_history->content);
		keep_track_history = keep_track_history->next;
		while (sh->input_str[++i])
			ft_putchar(sh->input_str[i]);
		if (sh->index_history < ft_historysize(history))
			sh->index_history++;
	}
}

void cmd_history_down(t_sh *sh, t_history *history, int cmd)
{
	int i;
	int j;

	t_history *keep_track_history;
	keep_track_history = history;
	i = -1;
	j = -1;
	if (sh->index_history >= ft_historysize(history))
		sh->index_history -= 2;
	while (++j < sh->index_history)
		keep_track_history = keep_track_history->next;
	if (history && keep_track_history)
	{
		char *cl = tgetstr("dl", NULL);
		tputs(cl, 1, &ft_putchar);
		char *cl1 = tigetstr("dll");
		tputs(cl1, 1, &ft_putchar);
		sh->input_str = ft_strdup(keep_track_history->content);
		write(0, "My Minishell ~> ", 16);
		keep_track_history = keep_track_history->next;
		while (sh->input_str[++i])
			ft_putchar(sh->input_str[i]);
		if (sh->index_history >= 0)
			sh->index_history--;
	}
}

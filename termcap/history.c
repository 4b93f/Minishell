/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:01:20 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/16 22:12:08 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <term.h>
#include <curses.h>
#include <termios.h>
#include <unistd.h>

static int	ft_historysize(t_history *lst)
{
	int	i;

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

void	cmd_history_up(t_sh *sh, t_history *history, int cmd)
{
	t_hist_s	*var;

	var->keep_track_history = history;
	var->i = -1;
	var->j = -1;
	if (sh->index_history == -1)
		sh->index_history += 2;
	while (++var->j < sh->index_history)
		var->keep_track_history = var->keep_track_history->next;
	if (history && var->keep_track_history)
	{
		var->cl = tgetstr("dl", NULL);
		tputs(var->cl, 1, &ft_putchar);
		var->cl1 = tigetstr("dll");
		tputs(var->cl1, 1, &ft_putchar);
		write(0, "My Minishell ~> ", 16);
		sh->input_str = ft_strdup(var->keep_track_history->content);
		var->keep_track_history = var->keep_track_history->next;
		while (sh->input_str[++var->i])
			ft_putchar(sh->input_str[var->i]);
		if (sh->index_history < ft_historysize(history))
			sh->index_history++;
	}
}

void	cmd_history_down(t_sh *sh, t_history *history, int cmd)
{
	t_hist_s	*var;

	var->keep_track_history = history;
	var->i = -1;
	var->j = -1;
	if (sh->index_history >= ft_historysize(history))
		sh->index_history -= 2;
	while (++var->j < sh->index_history)
		var->keep_track_history = var->keep_track_history->next;
	if (history && var->keep_track_history)
	{
		var->cl = tgetstr("dl", NULL);
		tputs(var->cl, 1, &ft_putchar);
		var->cl1 = tigetstr("dll");
		tputs(var->cl1, 1, &ft_putchar);
		sh->input_str = ft_strdup(var->keep_track_history->content);
		write(0, "My Minishell ~> ", 16);
		var->keep_track_history = var->keep_track_history->next;
		while (sh->input_str[++var->i])
			ft_putchar(sh->input_str[var->i]);
		if (sh->index_history >= 0)
			sh->index_history--;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:56:15 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/15 16:33:59 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <term.h>
#include <curses.h>
#include <termios.h>

void	actual_cursor_pos(t_sh *sh)
{
	char	tmp;
	char	*buf;
	int		x;
	int		ret;

	x = 0;
	sh->cursor_i = 0;
	sh->cursor_j = 0;
	buf = calloc(sizeof(char), 30);
	write(1, "\033[6n", 5);
	while (tmp != 'R')
	{
		read(1, &tmp, 1);
		buf[x] = tmp;
		x++;
	}
	x = 1;
	while (buf[++x] != ';')
		sh->cursor_i = sh->cursor_i * 10 + (buf[x] - '0');
	while (buf[++x] != 'R')
		sh->cursor_j = sh->cursor_j * 10 + (buf[x] - '0');
	return ;
}

void	delete(t_sh *sh)
{
	int		cut;
	char	*cm;
	char	*cm1;
	char	*dl;
	char	*dl1;

	if (sh->cursor_j >= 17)
	{
		cut = ft_strlen(sh->input_str);
		sh->cursor_j--;
		cm = tgetstr("cm", NULL);
		cm1 = tigetstr("cup");
		tputs(tgoto(cm, sh->cursor_j, sh->cursor_i), 1, &ft_putchar);
		dl = tgetstr("dc", NULL);
		tputs(dl, 1, &ft_putchar);
		dl1 = tigetstr("dchl");
		tputs(dl1, 1, &ft_putchar);
		sh->input_str[cut - 1] = '\0';
	}
}

int	termcap(t_sh *sh, t_history *history)
{
	int				ret;
	char			*term_type;
	struct termios	term;
	struct termios	restore;
	char			*buf;

	tcgetattr(0, &term);
	tcgetattr(0, &restore);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	sh->cursor_j -= 1;
	sh->cursor_i -= 1;
	term_type = env_lst_finder(sh->env_lst, "TERM")->content;
	ret = tgetent(NULL, term_type);
	if (ret == -1)
	{
		printf("Base de données non accesible\n");
		exit(0);
	}
	if (ret == 0)
	{
		printf("Pas d'info dans le base de données, ou trop peu\n");
		exit(0);
	}
	while (1)
	{
		buf = calloc(sizeof(char), 10);
		read(0, buf, 10);
		if (buf[0] == 127)
		{
			actual_cursor_pos(sh);
			sh->cursor_j -= 1;
			sh->cursor_i -= 1;
			tcsetattr(0, TCSANOW, &restore);
			delete(sh);
			tcsetattr(0, TCSANOW, &term);
			continue ;
		}	
		if (buf[0] == '\n')
		{
			sh->index_history = 0;
			break ;
		}
		if (buf[0] == 27)
		{
			if (buf[1] == '[')
			{
				if (buf[2] == 'A')
				{
					cmd_history_up(sh, history, UP);
					actual_cursor_pos(sh);
					sh->cursor_j -= 1;
					sh->cursor_i -= 1;
					tcsetattr(0, TCSANOW, &term);
					continue ;
				}
				if (buf[2] == 'B')
				{
					cmd_history_down(sh, history, UP);
					actual_cursor_pos(sh);
					sh->cursor_j -= 1;
					sh->cursor_i -= 1;
					tcsetattr(0, TCSANOW, &term);
					continue ;
				}
			}
		}
		else
		{
			sh->cursor_j++;
			tcsetattr(0, TCSANOW, &restore);
			write(1, buf, sizeof(buf));
			sh->input_str = ft_strjoin(sh->input_str, buf);
			tcsetattr(0, TCSANOW, &term);
		}
	}
	if (buf[0] == '\n' && sh->input_str)
		printf("\n");
	ret = setupterm(NULL, STDOUT_FILENO, NULL);
	tcsetattr(0, TCSANOW, &restore);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:04:42 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/19 18:26:110 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>
#include <curses.h>
#include <termios.h>
#include <unistd.h>


char	*get_actual_path(void)
{
	char	*buf;
	char	*str;
    size_t	size;

	buf = NULL;
	str = NULL;
    size = 10000;
	str = getcwd(buf, size);
	return (str);
}

static char	*argv_to_str(char **arg)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (arg && arg[i])
		str = ft_strjoinfree(str, arg[i++]);
	return (str);
}

void	ft_retval_init(t_sh *sh)
{
	t_env_lst	*ptr;
	char		*var;
	char		*val;

	var = ft_strdup("?");
	if (!var)
		ft_error(MALLOC_ERROR, sh, 0);
	val = ft_strdup("0");
	if (!val)
	{
		free(var);
		ft_error(MALLOC_ERROR, sh, 0);
	}
	ptr = ft_env_lstnew(var, val);
	if (!ptr)
		ft_error(MALLOC_ERROR, sh, 0);
	ft_env_lstadd_back(&sh->env_lst, ptr);
	
}

char *del_char(char *s1, int c)
{
	char *dup;
	int i;
	int j;

	dup = NULL;
	i = -1;
	j = -1;
	dup = malloc(sizeof(char*) * strlen(s1));
	if (!dup)
		return (NULL);
	while (s1[++i])
	{
		while (s1[i] == c)
			i++;
		dup[++j] = s1[i];
	}
	dup[++j] = '\0';
	free(s1);
	return (dup);
}

int parse_input(t_sh *sh)
{
	int i;
	int j;
	char *str;

	i = -1;
	j = -1;
	str = NULL;
	str = calloc(sizeof(char), ft_strlen(sh->input_str) + 1);
	while (sh->input_str[++i])
	{
		if (sh->input_str[i] == '\'')
			while (sh->input_str[++i] && sh->input_str[i] != '\'')
				str[++j] = sh->input_str[i];
		else if (sh->input_str[i] == '\"')
			while (sh->input_str[++i] && sh->input_str[i] != '\"')
				str[++j] = sh->input_str[i];
		else
			str[++j] = sh->input_str[i];
		
	}
	str[i] = '\0';
	sh->cmd->cmd_str = str;
	// printf("str == %s\n", str);
	return (1);
}

void actual_cursor_pos(t_sh *sh)
{
	char tmp;
	char *buf;
	int x;
	int ret;

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
		//printf("buf[%d]={%c} %d\n", i, tmp, tmp);
		//printf("{%s}\n", buf);
	}
	x = 1;
	while(buf[++x] != ';')
		sh->cursor_i = sh->cursor_i * 10 + (buf[x] - '0');
	while(buf[++x] != 'R')
		sh->cursor_j = sh->cursor_j * 10 + (buf[x] - '0');
	return ;
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

void cmd_history(t_sh *sh, t_history *history, int cmd)
{
	int i;

	i = -1;
	if (history)
	{
		char *cl = tgetstr("dl", NULL);
		tputs(cl, 1, &ft_putchar);
		char *cl1 = tigetstr("dll");
		tputs(cl1, 1, &ft_putchar);
		write(0, "My Minishell ~> ", 16);
		sh->input_str = ft_strdup(history->content);
		history = history->next;
		while (sh->input_str[++i])
			ft_putchar(sh->input_str[i]);
	}
}

void delete(t_sh *sh)
{
	char *dl = tgetstr("dc", NULL);
	tputs(dl, 1, &ft_putchar);
	char *dl1 = tigetstr("dchl");
	tputs(dl1 , 1, &ft_putchar);
}

int		termcap(t_sh *sh, t_history *history)
{
	int ret;
	char *term_type;
	struct termios term;
	struct termios restore;

	tcgetattr(0, &term);
	tcgetattr(0, &restore);
	term.c_lflag &= ~(ICANON|ECHO);
	term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	actual_cursor_pos(sh);
	//printf("%d et %d\n", sh->cursor_i, sh->cursor_j);
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
	char *buf;
	while(1)
	{
		buf = calloc(sizeof(char), 10);
		read(0, buf, 10);
		if (buf[0] == 127)
		{
			printf("!\n");
			tcsetattr(0, TCSANOW, &restore);
			delete(sh);
			tcsetattr(0, TCSANOW, &term);
		}	
		if (buf[0] == '\n')
			break;
		if (buf[0] == 27)
		{
			if (buf[1] == '[')
			{
				if (buf[2] == 'A')
				{
					cmd_history(sh, history, UP);
					tcsetattr(0, TCSANOW, &term);
				}
			}
		}
		else
		{
			tcsetattr(0, TCSANOW, &restore);
			write(1, buf, 1);
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

t_history	*ft_historylast(t_history *lst)
{
	t_history	*ptr;

	ptr = NULL;
	while (lst)
	{
		ptr = lst;
		lst = lst->next;
	}
	return (ptr);
}

void	ft_historyadd_front(t_history **alst, t_history *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

t_history	*ft_historynew(void *content)
{
	t_history	*ptr;
	
	ptr = malloc(sizeof(t_history));
	if (!ptr)
		return (NULL);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}

void	ft_print_history(t_history *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		printf("{,%s,}\n", lst->content);
		lst = lst->next;
	}
}

int		main(int argc, char **argv, char **env)
{
	t_sh	*sh;
	t_history *history;
	int		ret;
	char	buf[200];

	sh = ft_malloc_sh();
	if (!sh)
		ft_error(MALLOC_ERROR, sh, 0);
	ft_retval_init(sh);
	ft_env_to_lst(env, sh);
	if (!env_lst_finder(sh->env_lst, "PWD"))
		ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(ft_strdup("PWD"), get_actual_path()));
	if (!env_lst_finder(sh->env_lst, "SHLVL"))
		ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(ft_strdup("SHLVL"), ft_strdup("1")));
	else
		ft_set_free_env(sh, "SHLVL", ft_itoa(ft_atoi((char *)env_lst_finder(sh->env_lst, "SHLVL")->content) + 1));
	if (!env_lst_finder(sh->env_lst, "_"))
		ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(ft_strdup("_"), NULL));
	ret = 1;
	while(ret)
	{
		if (!sh->save_str)
			write(0, "My Minishell ~> ", 16);
		ret = termcap(sh, history);
		if (!sh->input_str)
		{
			printf("\n");
			continue;
		}
		ft_historyadd_front(&history, ft_historynew(sh->input_str));
		ft_print_history(history);
		//printf("{%s}\n", sh->input_str);
		get_all_path(sh);
		//if ((argc == 1 || ft_strcmp(argv[1], "-c")) && !sh->save_str)
		//	ret = get_next_line(0, &sh->input_str);
		//else if (!(ret = 0) && !sh->save_str)
		//	sh->input_str = argv_to_str(&argv[2]);
		//else
		//{
		//	ret = 1;
		//	sh->input_str = sh->save_str;
		//}
		strtolst(sh);
		parser(sh);
		executor(sh);
		sh_free(sh);
	}
	return (ft_atoi(env_lst_finder(sh->env_lst, "?")->content));
}

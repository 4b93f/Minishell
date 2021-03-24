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

int		termcap(t_sh *sh)
{
	int ret;
	int col_count;
	int line_count;
	char *term_type;
	char *cm_cap;
	char *cl_cap;
	int actual_pos;
	struct termios term;
	struct termios restore;

	tcgetattr(0, &term);
	tcgetattr(0, &restore);
	term.c_lflag &= ~(ICANON|ECHO);
	term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	//actual_cursor_pos(sh);
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
	ret = setupterm(NULL, STDOUT_FILENO, NULL);
	tcsetattr(0, TCSANOW, &restore);
	//char *ks = tgetstr("ks", NULL);

	sh->tc_kl = tgetstr("kl", NULL);
	sh->tc_kr = tgetstr("kr", NULL);
	sh->tc_ku = tgetstr("ku", NULL);
	sh->tc_kd = tgetstr("kd", NULL);
	char buf[64] = {0};
	ret = read(STDIN_FILENO, buf, 64);
	buf[ret] = '\0';
    if (buf[0] == 27)
    {
        if (buf[1] == '[')
        {
            if (buf[2] == sh->tc_ku[2])
            	printf("fleche du haut\n");
        	else if (buf[2] == sh->tc_kd[2])
                printf("fleche du bas\n");
            else if (buf[2] == sh->tc_kr[2])
				 printf("fleche de droite\n");
            else if (buf[2] == sh->tc_kl[2])
            	printf("fleche gauche\n");
        }
    }
	exit(0);
	return (1);
}
/*
int termcap(t_sh *sh)
{
	char *buf;
	WINDOW *ecran;
	char *term_type;
	int success;
	int height;
	int width;
	char *cl;
	char *cm;
	char PC;
	char *BC;
	char *UP;

	buf = calloc(sizeof(char), 48);
	term_type = env_lst_finder(sh->env_lst, "TERM")->content;
	printf("%s\n", term_type);
	success = tgetent(buf, term_type);
	if (success < 0)
		printf("Could not access the termcap data base.\n");
	if (success == 0)
		printf("Terminal type is not defined\n");
	cl = tgetstr("cl", &buf);
	cm = tgetstr("cm", &buf);
	height = tgetnum ("li");
  	width = tgetnum ("co");
	BC = tgetstr ("le", &buf);
	UP = tgetstr ("up", &buf);
	getmaxy();
	exit(0);
}
*/

int		main(int argc, char **argv, char **env)
{
	t_sh	*sh;
	int		ret;

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
		get_all_path(sh);
		if (!sh->save_str)
			write(0, "My Minishell ~> ", 16);
		if ((argc == 1 || ft_strcmp(argv[1], "-c")) && !sh->save_str)
			ret = get_next_line(0, &sh->input_str);
		else if (!(ret = 0) && !sh->save_str)
			sh->input_str = argv_to_str(&argv[2]);
		else
		{
			ret = 1;
			sh->input_str = sh->save_str;
		}
		termcap(sh);
		strtolst(sh);
		parser(sh);
		executor(sh);
		sh_free(sh);
	}
	return (ft_atoi(env_lst_finder(sh->env_lst, "?")->content));
}

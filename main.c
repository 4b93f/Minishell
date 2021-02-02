/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:04:42 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/02 00:25:11 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_actual_path(void)
{
	char	*buf;
	char	*str;
    size_t	size;

	buf = NULL;
    size = 10000;
	str = getcwd(buf, size);
	return (str);
}

int		check_syntax(t_sh *sh)
{
	int i;
	int error;

	i = -1;
	error = 0;
	while (sh->input_str[++i])
	{
		if (sh->input_str[i] == '\\' && sh->input_str[i + 1] == ';')
			error++;
	}
	return (error);
}

static char	*argv_to_str(char **arg)
{
	int		i;
	char	*tmp;
	char	*str;

	i = 0;
	str = NULL;
	// if (arg && arg[i])
	while (arg && arg[i])
	{
		tmp = str;
		str = ft_strjoin(tmp, arg[i]);
		free(tmp);
		i++;
	}
	return (str);
}

int		main(int argc, char **argv, char **env)
{
	t_sh	*sh;
	int		ret;

	sh = ft_malloc_sh();
	ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(ft_strdup("?"), ft_strdup("0")));
	ft_env_to_lst(env, sh);
	ret = 1;
	while(ret)
	{
		get_all_path(sh);
		write(0, "My Minishell ~> ", 16);
		
		if (argc == 1 || ft_strcmp(argv[1], "-c")) //	le temps des tests
			ret = get_next_line(0, &sh->input_str);
		else
		{
			sh->input_str = argv_to_str(&argv[2]);
			ret = 0; //		le temps des tests.
		}
		strtolst(sh);
		parser(sh);

		executor(sh);
		sh_free(sh);
	}
	ft_error(0, sh, ft_atoi(env_lst_finder(sh->env_lst, "?")->content));
	return (0);
}

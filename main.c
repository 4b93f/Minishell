/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:04:42 by chly-huc          #+#    #+#             */
/*   Updated: 2021/01/31 21:52:12 by jsilance         ###   ########.fr       */
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
	ft_env_to_lst(env, sh);
	get_all_path(sh);
	ret = 1;
	
		printf("[%s] DETECTED!\n", argv[1]);
	// if (!ft_strcmp(argv[1], "-n"))
		// printf("[-n] DETECTED!\n");
	
	while(ret)
	{
		int i = -1;
		write(0, "My Minishell ~> ", 16);
		ret = get_next_line(0, &sh->input_str);

		strtolst(sh);
		parser(sh);

		executor(sh);
		sh_free(sh);
	}
	//ft_free
	//ft_env_lstclear(&sh->env_lst, free);
	//sh_free(sh);
	//free(sh);
	ft_error(0, sh);
	return (1);
}

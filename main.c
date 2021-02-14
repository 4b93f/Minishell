/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:04:42 by chly-huc          #+#    #+#             */
/*   Updated: 2021/02/14 17:05:23 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// if (!env_lst_finder(sh->env_lst, "_"))
		// ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(ft_strdup("_"), NULL));
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
	// printf("[%d]\n", ret);
	ft_error(0, sh, ft_atoi(env_lst_finder(sh->env_lst, "?")->content));
	return (0);
}

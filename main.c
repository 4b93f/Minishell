/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:06:09 by shyrno            #+#    #+#             */
/*   Updated: 2021/10/10 23:50:59 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct/struct.h"

int	g_in_loop = 0;

//void	ctrl_c(int c)
//{
//	(void)c;
//	write(2, "\n", 1);
//	rl_replace_line("", 0);
//	rl_on_new_line();
//	if (g_in_loop == 0)
//		rl_redisplay();
//}

void	prompt(t_sh *sh)
{
	sh->input_str = readline("My Minishell ~> ");
	if (sh->input_str)
		add_history(sh->input_str);
}

int	read_l(t_sh *sh)
{
	get_all_path(sh);
	prompt(sh);
	g_in_loop = 1;
	if (!sh->input_str)
	{
		sh_free(sh);
		exit(0);
	}
	if (!ft_strcmp(sh->input_str, ""))
	{
		g_in_loop = 0;
		return (0);
	}
	if (!ver_quote(sh->input_str))
	{
		sh_free(sh);
		g_in_loop = 0;
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	int		ret;
	t_sh	*sh;

	(void)argc;
	(void)argv;
	ret = 1;
	sh = ft_malloc_sh();
	if (!sh)
		return (0);
	env_setup(sh, env);
	//signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (ret)
	{
		if (!read_l(sh))
			continue ;
		sh->input_str = dollarz(sh, sh->input_str);
		if (sh->input_str)
			setup_engine(sh);
		g_in_loop = 0;
	}
	return (0);
}

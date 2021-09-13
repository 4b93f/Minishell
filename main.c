/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:06:09 by shyrno            #+#    #+#             */
/*   Updated: 2021/09/13 02:13:37 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct/struct.h"


int main(int argc, char **argv, char **env)
{
	int ret;
	t_sh *sh;

	sh = ft_malloc_sh();
	env_setup(sh, env);
	ret = 1;
	(void)argc;
	(void)argv;
	while(ret)
	{
		get_all_path(sh);
		// if(!(sh->input_str = readline("My Minishell ~> ")))
		//  	add_history(sh->input_str);
		ft_putstr_fd("My minishell ~> ", 2);
		ret = get_next_line(0, &sh->input_str);
		if (!ft_strcmp(sh->input_str, ""))
			continue;
		sh->input_str = dollarz(sh, sh->input_str);
		str_tolst(sh->input_str, sh);
		quoting(sh);
		//ft_print_lst(sh->lst_cmd);
		sh->ptr_cmd = sh->lst_cmd;
		exec(sh, sh->lst_cmd);
		sh_free(sh); 
		waitpid(-1, &sh->child_pid, 0);
		if(sh->stat != 1 && sh->stat != 0)
			return (0);
		exit(0);
	}
	return (0);
}

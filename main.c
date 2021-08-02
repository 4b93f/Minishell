/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:06:09 by shyrno            #+#    #+#             */
/*   Updated: 2021/07/30 19:14:33 by chly-huc         ###   ########.fr       */
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
		if(!(sh->input_str = readline("My Minishell ~> ")))
			add_history(sh->input_str);
		if (!ft_strcmp(sh->input_str, ""))
			continue;
		sh->input_str = dollarz(sh, sh->input_str);
		str_tolst(sh->input_str, sh);
		ft_print_lst(sh->lst_cmd);
		pipe_n_red(sh);
		start(sh);
		sh_free(sh);
	}
	return (TRUE);
	
}



//void	init_parser(t_parsing *parser)
//{
//	parser->quote = 0;
//	parser->pos = 0;
//	parser->final = NULL;
//}


/*
t_parsing parser;
	init_parser(&parser);

tmp = parsing(&parser, sh->input_str);
if (tmp == NULL)
{
	write(1, "parsing error\n", 14);
	return (-1);
}
printf("tmp = %s\n", tmp);
		
		*while (*tmp)
		{
tmp = sh->input_str;
			tmp = str_to_lst(tmp, sh);
			printf("{%s}\n", sh->cmd->cmd);
			sh->cmd = sh->cmd->next;


if (first_parsing(&parser, argv[1]) == -1)
{
	printf("PARSING_ERROR");
	return (-1);
}
if (flush_buff(&parser) == -1)
	return (-1);
if (fill_cmd(&cmd, parser.final) == -1)
	return (-1);
printf("final : |%s|\n", parser.final);
return (1);
*/
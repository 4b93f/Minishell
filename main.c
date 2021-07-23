/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:06:09 by shyrno            #+#    #+#             */
/*   Updated: 2021/07/23 16:35:18 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct/struct.h"

//void	init_parser(t_parsing *parser)
//{
//	parser->quote = 0;
//	parser->pos = 0;
//	parser->final = NULL;
//}

int main(int argc, char **argv, char **env)
{
    char *line;

    line = NULL;
    line = readline("My Minishell ~> ");
    printf("%s\n", line);
    exit(0);
	int ret;
	t_sh *sh;
	//char *line;
	//char *tmp;
	//t_parsing parser;

	sh = ft_malloc_sh();
	//init_parser(&parser);
	//env_setup(sh, env);
	//ret = 1;
	(void)argc;
	(void)argv;
	while(1)
	{
		sh->input_str = readline("My Minishell ~> ");
		printf("[%s]\n", sh->input_str);
		//write(0, "My Minishell ~> ", 16);
		//get_next_line(0, &sh->input_str);
		//if (!ft_strcmp(sh->input_str, ""))
		//	continue;
		//sh->input_str = dollarz(sh, sh->input_str);
		//str_tolst(sh->input_str, sh);
		//ft_print_lst(sh->lst_cmd);
		
		//start(sh);
		//free(sh->input_str);
		//sh_free(sh);
		//printf("<<%s>>\n", tmp);
		//tmp = parsing(&parser, sh->input_str);
		//if (tmp == NULL)
		//{
		//	write(1, "parsing error\n", 14);
		//	return (-1);
		//}
		//printf("tmp = %s\n", tmp);
		/*while (*tmp)
		{
			//tmp = sh->input_str;
			tmp = str_to_lst(tmp, sh);
			printf("{%s}\n", sh->cmd->cmd);
			sh->cmd = sh->cmd->next;
		}*/
	}
	return (1);

	//if (first_parsing(&parser, argv[1]) == -1)
	//{
	//	printf("PARSING_ERROR");
	//	return (-1);
	//}
	//if (flush_buff(&parser) == -1)
	//	return (-1);
	//if (fill_cmd(&cmd, parser.final) == -1)
	//	return (-1);
	//printf("final : |%s|\n", parser.final);
	//return (1);
}

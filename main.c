#include "parser.h"


void	init_parser(t_parsing *parser)
{
	parser->quote = 0;
	parser->pos = 0;
	parser->final = NULL;
}



int main(int argc, char **argv)
{
	int ret;
	char *tmp;
	t_parsing parser;
	t_sh *sh;

	init_parser(&parser);
	sh = ft_malloc_sh();
	ret = 1;
	(void)argc;
	(void)argv;
	while(ret)
	{
		write(0, "My Minishell ~> ", 16);
		get_next_line(0, &sh->input_str);
		tmp = parsing(&parser, sh->input_str);
		if (tmp == NULL)
		{
			write(1, "parsing error\n", 14);
			return (-1);
		}
		printf("tmp = %s\n", tmp);
		/*while (*tmp)
		{
			//tmp = sh->input_str;
			tmp = str_to_lst(tmp, sh);
			printf("{%s}\n", sh->cmd->cmd);
			sh->cmd = sh->cmd->next;
		}*/
		ret = 0;
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

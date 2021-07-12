#include "parser.h"

int flush_buff(t_parsing *parser)
{
	int i;
	parser->buff[parser->pos] = '\0';
	if (!parser->final)
	{
		parser->final = malloc(sizeof(char) * parser->pos);
		if (parser->final == NULL)
			return (-1);
		i = -1;
		while (parser->buff[++i])
				parser->final[i] = parser->buff[i];
	}
	else
	{
		if (ft_strjoin(parser->final, parser->buff) == NULL)
			return (-1);
	}
	return (0);
}

int	c_in_buff(t_parsing *parser, char c)
{
	if (parser->pos + 1 == BUFF_MAX)
	{
			if (flush_buff(parser) == -1)
				return (-1);
	}
	parser->buff[parser->pos] = c;
	parser->pos++;
	return (0);
}
void	init_parser(t_parsing *parser)
{
	parser->quote = 0;
	parser->pos = 0;
	parser->final = NULL;
}

int	quoting(t_parsing *parser, char c)
{
	if (c == 39)
	{
		if (parser->quote == NONE)
			return (QUOTE);
		else if (parser->quote == D_QUOTE)
			return (D_QUOTE);
		else
			return (NONE);
	}
	else
	{
		if (parser->quote == NONE)
			return (D_QUOTE);
		else if (parser->quote == QUOTE)
			return (QUOTE);
		else
			return (NONE);
	}
}

int first_parsing(t_parsing *parser, char *cmd)
{
	int i;

	i = -1;
	while(cmd[++i])
	{
		if (cmd[i] == 39 || cmd[i] == 34)
		{
			parser->quote = quoting(parser, cmd[i]);
			i++;
		}
		//else if (cmd[i] == '$' && parser->quote != QUOTE)
			//do_dollars
		else if (cmd[i] == ' ')
		{
			if (parser->quote == NONE)
				cmd[i] = -1;
		}
		if (c_in_buff(parser, cmd[i]) == -1)
			return (-1);
	}
	if (parser->quote != NONE)
		return (-1);
	return (0);
}



int main(int argc, char **argv)
{
	int ret;
	char *tmp;
	t_parsing parser;
	t_sh *sh;
	//t_cmd cmd;

	init_parser(&parser);
	sh = ft_malloc_sh();
	ret = 1;
	(void)argc;
	(void)argv;
	while(ret)
	{
		write(0, "My Minishell ~> ", 16);
		get_next_line(0, &sh->input_str);
		tmp = sh->input_str;
		while (*tmp)
		{
			//tmp = sh->input_str;
			tmp = str_to_lst(tmp, sh);
			printf("{%s}\n", sh->cmd->cmd);
			sh->cmd = sh->cmd->next;
		}
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

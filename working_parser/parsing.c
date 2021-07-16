#include "parser.h"

int	flush_buff(t_parsing *parser)
{
	int	i;

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

int	first_parsing(t_parsing *parser, char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == 39 || cmd[i] == 34)
		{
			parser->quote = quoting(parser, cmd[i]);
			i++;
		}
		if (cmd[i] == '$' && parser->quote != QUOTE)
		{
			if (cmd[i] == ' ')
			{
				if (parser->quote == NONE)
				{
					while (cmd[i + 1] == ' ')
						i++;
				}
			}
		}
		if (c_in_buff(parser, cmd[i]) == -1)
			return (-1);
	}
	if (parser->quote != NONE)
		return (-1);
	return (0);
}

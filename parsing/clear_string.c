#include "../parser.h"

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
			cmd[i] = -1;
		}
			//else if (cmd[i] == '$' && parser->quote != QUOTE)
			//do_dollars
		else if (cmd[i] == ' ')
		{
			if (parser->quote == NONE)
				cmd[i] = -1;
		}
		else if (cmd[i] == '|' && parser->quote == NONE)
			cmd[i] = -2;
		if (c_in_buff(parser, cmd[i]) == -1)
			return (-1);
	}
	if (parser->quote != NONE)
		return (-1);
	return (0);
}

char *parsing(t_parsing *parser, char *cmd)
{

	if (first_parsing(parser, cmd) == -1)
		return (NULL);
	if (flush_buff(parser) == -1)
		return (NULL);
	return (parser->final);
}
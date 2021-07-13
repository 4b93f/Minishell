#include "../parser.h"

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
	parser->pos = 0;
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
	//printf("%c", parser->buff[parser->pos]);
	parser->pos++;
	return (0);
}
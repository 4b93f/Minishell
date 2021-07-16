/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:37:15 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/15 16:37:56 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	isolate_cmd(char *dest, char **str)
{
	int		i;
	int		count;
	char	*tmp;

	while (**str != ' ')
	{
		(*str)++;
		count++;
	}
	while (**str + 1 == ' ')
	{
		(*str)++;
		count++;
	}
	dest = malloc(sizeof(char) * count);
	if (dest == NULL)
		return (-1);
	i = 0;
	tmp = *str;
	while (i < count)
	{
		dest[i] == tmp[i];
		i++;
	}
	return (0);
}

int	fill_cmd(t_cmd *cmd, char *str)
{
	while (*str == ' ')
		str++;
	if (isolate_cmd(cmd->cmd, &str) == -1)
		return (-1);
}

int	main(int argc, char **argv)
{
	t_parsing	parser;
	t_cmd		cmd;

	init_parser(&parser);
	(void)argc;
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
}

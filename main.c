/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:06:09 by shyrno            #+#    #+#             */
/*   Updated: 2021/08/06 17:10:34 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct/struct.h"


t_lst_cmd *next_sep(t_sh *sh, t_lst_cmd *ptr)
{
	if (!ptr) 
		return (NULL);
	while(ptr)
	{
		if (str_sep(ptr->cmd) && ptr->next)
		{
			((t_lst_cmd*)ptr->next)->type = PIPE; 
			return (ptr->next);
		}
		ptr = ptr->next;
	}
	return (NULL);	
}


t_lst_cmd *previous_sep(t_sh *sh, t_lst_cmd *ptr)
{
	t_lst_cmd *tmp;
	t_lst_cmd *parse;
	t_lst_cmd *stock;
	if ((cmd_lstsize(ptr) - cmd_lstsize(sh->lst_cmd)) == 0)
		return (NULL);
	parse = sh->lst_cmd;
	stock = parse;
	while (parse)
	{
		stock = parse;
		parse = next_sep(sh, parse);
		if (ptr == parse)
			return(stock);
		if (parse == NULL)
			return(stock);
	}
	return (NULL);
}


void tmp(t_sh *sh, t_lst_cmd *token)
{
	int pid;
	t_lst_cmd *next;
	t_lst_cmd *prev;

	pid = 0;
	next = next_sep(sh, token);
	prev = previous_sep(sh, token);
	printf("tokeeeeen[%s]\n", token->cmd);
	//if (!next)
	//	printf("next == NULL\n");
	//else
	//	printf("next ==[%s]\n", next->cmd);
	//if (!prev)
	//	printf("prev == NULL\n");
	//else
	//	printf("prev ==[%s]\n", prev->cmd);
	if (prev && prev->type == PIPE)
		(void)NULL;
	if (next && pid != 1)
	{
		sh->ptr_cmd = next;
		tmp(sh, next);
	}
	if (prev && prev->type == PIPE && pid != 1)
	{
		sh->ptr_cmd = token;
	}
	exit(0);
}

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
		sh->ptr_cmd = sh->lst_cmd;
		tmp(sh, sh->lst_cmd);
		exit(0);
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
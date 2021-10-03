/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:06:09 by shyrno            #+#    #+#             */
/*   Updated: 2021/09/30 17:57:40 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct/struct.h"

int g_in_loop = 0;

t_lst_cmd *prev_token(t_sh *sh, t_lst_cmd *ptr)
{
	t_lst_cmd *parse;
	t_lst_cmd *stock;

	if ((cmd_lstsize(ptr) - cmd_lstsize(sh->lst_cmd)) == 0)
		return (NULL);
	parse = sh->lst_cmd;
	stock = parse;
	while (parse)
	{
		stock = parse;
		parse = parse->next;
		if (ptr == parse)
			return(stock);
		if (parse == NULL)
			return(stock);
	}
	return (NULL);
}

t_lst_cmd *next_token(t_lst_cmd *ptr)
{
	if(!ptr)
		return(NULL);
	return(ptr->next);
}

void get_type(t_lst_cmd *cmd, t_lst_cmd *prev)
{
	if (!prev || (prev->type != ARG && prev->type != CMD))
		cmd->type = CMD;
	else
		cmd->type = ARG;
}

t_lst_cmd *next_sep2(t_lst_cmd *ptr)
{
	if (!ptr) 
		return (NULL);
	while(ptr)
	{
		if (str_sep(ptr->cmd))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);	
}

int index_token(t_sh *sh, t_lst_cmd *ptr)
{
	int i;
	t_lst_cmd *parse;

	i = 0;
	if (!ptr)
		return(-1);
	parse = sh->lst_cmd;
	while(parse)
	{
		if (parse == ptr)
			return (i);
		parse = parse->next;
		i++;
	}
	return(i);
}

t_lst_cmd *prev_sep(t_sh *sh, t_lst_cmd *ptr)
{	
	int index;
	t_lst_cmd *stock;
	t_lst_cmd *token;
	t_lst_cmd *parse;

	token = NULL;
	index = index_token(sh, ptr);
	parse = sh->lst_cmd;
	while(parse)
	{
		stock = token;
		token = next_sep2(parse);
		if (index_token(sh, token) >= index || index_token(sh, token) == -1)
			return(stock);
		parse = parse->next;
	}
	return(NULL);
}

void	ft_swar(t_sh *sh)
{
	t_lst_cmd	*first;
	t_lst_cmd *stock;

	first = sh->lst_cmd;
	sh->ptr_cmd = sh->_lst_cmd;
	sh->ptr_cmd = sh->ptr_cmd->next;
	while (sh->ptr_cmd)
	{
		stock = sh->ptr_cmd->content;
		sh->ptr_cmd->content = first->content;
		first->content = stock;
		sh->ptr_cmd = sh->ptr_cmd->next;
	}
	printf("rra\n");
}

void swap(t_sh *sh)
{
	t_lst_cmd *stock;

	sh->ptr_cmd = sh->lst_cmd;
	stock = sh->ptr_cmd->cmd;
	while (sh->ptr_cmd->next)
	{
		sh->ptr_cmd->cmd = ((t_lst_cmd*)sh->ptr_cmd->next)->cmd;
		sh->ptr_cmd = sh->ptr_cmd->next;
	}
	sh->ptr_cmd->cmd = stock;
	printf("ra\n");
}

int verif_syntax(t_sh *sh)
{
	t_lst_cmd *prev;
	t_lst_cmd *next;
	sh->ptr_cmd = sh->lst_cmd;

	// if (sh->ptr_cmd)
	// 	if (!ft_strcmp(sh->ptr_cmd->cmd, "|") || !ft_strcmp(sh->ptr_cmd->cmd, "<") || !ft_strcmp(sh->ptr_cmd->cmd, "<<") || !ft_strcmp(sh->ptr_cmd->cmd, ">")
	// 	|| !ft_strcmp(sh->ptr_cmd->cmd, ">>"))
	// 		return (2);
	// while (sh->ptr_cmd)
	// {
	// 	if (sh->ptr_cmd->next)
	// 		if (sh->ptr_cmd->type && ((t_lst_cmd *)sh->ptr_cmd->next)->type)
	// 			return(2);
	// 	sh->ptr_cmd = sh->ptr_cmd->next;
	// }

	while(sh->ptr_cmd)
	{
		prev = prev_token(sh, sh->ptr_cmd);
		next = next_token(sh->ptr_cmd);
		(void)next;
		if (!sh->ptr_cmd->type)
			get_type(sh->ptr_cmd, prev);
		sh->ptr_cmd = sh->ptr_cmd->next;
	}
	sh->ptr_cmd = sh->lst_cmd;
	prev = sh->lst_cmd;
	while(sh->ptr_cmd)
	{
		prev = prev_sep(sh, sh->ptr_cmd);
		if (prev && sh->ptr_cmd->type == ARG)
		{
			if (prev->type == RIGHT || prev->type == DRIGHT || prev->type == LEFT || prev->type == DLEFT)
			{
				printf("{%s}\n", sh->ptr_cmd->cmd);
			}
		}
		sh->ptr_cmd = sh->ptr_cmd->next;
	}
	return (0);
}

void ctrl_d()
{
	exit(0);
}

// void ctrl_c()
// {
// 	write(2, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	if (g_in_loop == 0)
// 		rl_redisplay();
// }

void prompt(t_sh *sh)
{
	if(!(sh->input_str = readline("My Minishell ~> ")))
		add_history(sh->input_str);
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
	//signal(SIGINT, &ctrl_c);
	signal(SIGKILL, &ctrl_d);
	while(ret)
	{
		get_all_path(sh);
		prompt(sh);
		g_in_loop = 1;
		if (!ft_strcmp(sh->input_str, ""))
		{
			g_in_loop = 0;
			continue;
		}
		if (!ver_quote(sh->input_str))
		{
			sh_free(sh);
			g_in_loop = 0;
			continue;
		}
		sh->input_str = dollarz(sh, sh->input_str);
		if (sh->input_str)
		{
			str_tolst(sh->input_str, sh);
			//ft_print_lst(sh->lst_cmd);
			quoting(sh);

			if (!verif_syntax(sh))
			{
				exit(0);
				sh->ptr_cmd = sh->lst_cmd;
				exec(sh, sh->lst_cmd);
				sh_free(sh); 
				waitpid(-1, &sh->child_pid, 0);
				if (WIFEXITED(sh->child_pid))
					sh->child_pid = WEXITSTATUS(sh->child_pid);
				if (sh->stat == 1)
					exit(sh->exit_code);
				else if (sh->stat == 2)
					exit_code(sh, sh->child_pid);
				else
					exit_code(sh, sh->exit_code);	
				sh->stat = 0;
				sh->ret = 0;
				sh->child_pid = 0;
			}
			else
				exit_code(sh, 2);
		}
		g_in_loop = 0;
	}
	return(0);
}

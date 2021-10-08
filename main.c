/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:06:09 by shyrno            #+#    #+#             */
/*   Updated: 2021/10/08 10:25:52 by chly-huc         ###   ########.fr       */
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

void type(t_lst_cmd *cmd, t_lst_cmd *prev)
{	
	if (prev)
		if (prev->type == RIGHT || prev->type == LEFT || prev->type == DRIGHT || prev->type == DLEFT)
			cmd->redirected = 1;
	if (cmd->type)
		(void)NULL;
	else if (!prev || (prev->type != ARG && prev->type != CMD))
		cmd->type = CMD;
	else
		cmd->type = ARG;
}

void get_type(t_sh *sh)
{
	t_lst_cmd *prev;
	t_lst_cmd *next;
	sh->ptr_cmd = sh->lst_cmd;
	while(sh->ptr_cmd)
	{
		prev = prev_token(sh, sh->ptr_cmd);
		next = next_token(sh->ptr_cmd);
		(void)next;
		if(!sh->ptr_cmd->type)
			type(sh->ptr_cmd, prev);
		sh->ptr_cmd = sh->ptr_cmd->next;
	}
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

int get_redir_number(t_sh *sh)
{
	int i;

	i = 0;
	sh->ptr_cmd = sh->lst_cmd;
	while (sh->ptr_cmd)
	{
		if (sh->ptr_cmd->redirected == 1)
			i++;
		sh->ptr_cmd = sh->ptr_cmd->next;
	}
	return(i);
}

void	lst_cmdedit(char *cmd, int type, t_lst_cmd *ptr)
{
	ptr->cmd = cmd;
	ptr->type = type;
}

t_lst_cmd *del_one(t_lst_cmd *lst)
{
	t_lst_cmd	*ptr_lst;

	if (!lst)
		return (NULL);
	ptr_lst = lst;
	lst = lst->next;
	free(ptr_lst);
	return(ptr_lst);
}

void go_end(t_sh *sh, t_lst_cmd *token)
{
	t_lst_cmd *last;
	t_lst_cmd *stock;
	(void)last;
	stock = sh->lst_cmd;
	cmd_lstaddback(&sh->lst_cmd, cmd_lstnew(ft_strdup(token->cmd), token->type));
	token->type = -1;
}

t_lst_cmd *new_lst(t_sh *sh)
{
	t_lst_cmd *new_lst;
	t_lst_cmd *ptr_cmd;


	new_lst = NULL;
	ptr_cmd = sh->lst_cmd;
	while(ptr_cmd)
	{
		if (ptr_cmd->type != -1)
			cmd_lstaddback(&new_lst, cmd_lstnew(ft_strdup(ptr_cmd->cmd), ptr_cmd->type));
		ptr_cmd = ptr_cmd->next;
	}
	return(new_lst);
}

int verif_syntax(t_sh *sh)
{
	t_lst_cmd *prev;
	t_lst_cmd *tmp;
	int i;
	
	sh->ptr_cmd = sh->lst_cmd;
	if (sh->ptr_cmd)
	 	if (!ft_strcmp(sh->ptr_cmd->cmd, "|") || !ft_strcmp(sh->ptr_cmd->cmd, "<") || !ft_strcmp(sh->ptr_cmd->cmd, "<<") || !ft_strcmp(sh->ptr_cmd->cmd, ">")
	 	|| !ft_strcmp(sh->ptr_cmd->cmd, ">>"))
	 		return (2);
	prev = sh->lst_cmd;
	tmp = sh->lst_cmd;
	get_type(sh);
	i = get_redir_number(sh);
	i *= 2;
	while(tmp && i > 0)
	{
		if (tmp->type == RIGHT || tmp->type == DRIGHT || tmp->type == LEFT || tmp->type == DLEFT || tmp->redirected == 1)
		{
			go_end(sh, tmp);
			i--;
		}
		tmp = tmp->next;
	}
	tmp = sh->lst_cmd;
	sh->lst_cmd = new_lst(sh);
	cmd_lstclear(&tmp, free);
	return(0);
}

void ctrl_c()
{
	write(2, "\n", 1);
 	rl_replace_line("", 0);
 	rl_on_new_line();
 	if (g_in_loop == 0)
 		rl_redisplay();
}

void prompt(t_sh *sh)
{
	sh->input_str = readline("My Minishell ~> ");
	if (sh->input_str)
		add_history(sh->input_str);
}

void engine(t_sh *sh)
{
	str_tolst(sh->input_str, sh, 0, 0);
	quoting(sh);
	if (!sh->lst_cmd)
		return;
	if (!verif_syntax(sh))
	{
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
	{
		sh_free(sh);
		exit_code(sh, 2);
	}
}

int read_l(t_sh *sh)
{
	get_all_path(sh);
	prompt(sh);
	g_in_loop = 1;
	if (!sh->input_str)
	{
		sh_free(sh);
		exit(0);
	}
	if (!ft_strcmp(sh->input_str, ""))
	{
		g_in_loop = 0;
		return(0);
	}
	if (!ver_quote(sh->input_str))
	{
		sh_free(sh);
		g_in_loop = 0;
		return(0);
	}
	return(1);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	int ret;
	t_sh *sh;

	ret = 1;
	sh = ft_malloc_sh();
	env_setup(sh, env);
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while(ret)
	{
		if(!read_l(sh))
			continue;
		sh->input_str = dollarz(sh, sh->input_str);
		if (sh->input_str)
			engine(sh);
		g_in_loop = 0;
	}
	return(0);
}

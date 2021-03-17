/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:54:40 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/17 16:07:34 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include "executor.h"

static void	ft_sort_export(t_sh *sh, t_cmd_lst *cmd)
{
	char		*tmp;
	char		**tab;
	int			size;
	int			i;
	int			j;

	i = -1;
	size = ft_env_lstsize(sh->env_lst);
	tab = ft_lst_to_tab(sh->env_lst);
	if (!tab)
		return ;
	while (++i < size)
	{
		j = i;
		while (++j < size)
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
	}
	i = -1;
	while (tab && tab[++i])
	{
		if (!ft_strcmp(tab[i], "?") || !ft_strcmp(tab[i], "_"))
			continue ;
		print_declare(sh, cmd, tab, i);
	}
	free_tab(tab);
}

void		ft_export(t_cmd_lst *cmd, t_sh *sh)
{
	int			equal_pos;
	char		*var;
	char		*value;
	t_env_lst	*chainon;
	t_list		*ptr_str;

	value = NULL;
	ptr_str = cmd->str;
	if (!ptr_str)
	{
		ft_sort_export(sh, cmd);
		return ;
	}
	while (ptr_str)
	{
		//printf("{%s}\n", ptr_str->content);
		if (ft_strchr(ptr_str->content, '\\'))
		{
			ptr_str->content = ft_backslash(ptr_str->content);
			value = ft_strchr(ptr_str->content, '=');
			if (ft_strchr(ptr_str->content, '_') || ft_strchr(ptr_str->content, '0'))
				(void)NULL;
			else if (ft_strchr(value, ' '))
				ptr_str->content = fulltrim(ptr_str->content, ' ');
			else if (ft_str_isalnum(ptr_str->content) || !value)
			{
				printf("minishell: export:");
				ft_print_error(NOT_VALID_ID, ptr_str->content);
				env_lst_finder(sh->env_lst, "?")->content = ft_itoa(1);
				//printf("PASS\n");
				//free(value);
				return ;
			}
		}
		value = ft_strchr(ptr_str->content, '=');
		if (value)
			equal_pos = ft_strchr(ptr_str->content, '=') - (char *)ptr_str->content;
		value = NULL;
		if (!equal_pos)
			continue ;
		// printf("{%s}\n", ptr_str->content);
		var = ft_substr(ptr_str->content, 0, equal_pos - 1);
		if (!var)
			return;
		if (ft_atoi(var) || equal_pos == 1)
		{
			printf("minishell: export:");
			ft_print_error(NOT_VALID_ID, ptr_str->content);
			ft_set_free_env(sh, "?", ft_strdup("1"));
			free(var);
			return ;
		}
		var = rm_guim(var);

		//if (ft_str_isalnum(var))
		//{
			//printf("!\n");
			//ft_putstr_fd("minishell: syntax error near unexpected token '", cmd->fd_pipe_out);
			//write(cmd->fd_pipe_out, ft_str_isalnum(var), 1);
			//write(cmd->fd_pipe_out, "'\n", 2);
			//free(env_lst_finder(sh->env_lst, "?")->content);
			//env_lst_finder(sh->env_lst, "?")->content = ft_itoa(2);
			//free(var);
			//return ;
		//}
		ptr_str = ptr_str->next;
		free(var);
	}
	ptr_str = cmd->str;
	chainon = NULL;
	while (ptr_str)
	{
		if (ft_strchr(ptr_str->content, 61))
		{
			equal_pos = ft_strchr(ptr_str->content, 61) - (char *)ptr_str->content;
			var = ft_substr(ptr_str->content, 0, equal_pos - 1);
			value = ft_substr(ptr_str->content, equal_pos, ft_strlen(ptr_str->content));
		// printf("[%s]\n", value);
			chainon = env_lst_finder(sh->env_lst, var);
			if (!chainon)
				ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(var, value));
			else
			{
				free(var);
				if (chainon)
				{	
					free(chainon->content);
					chainon->content = value;
				}
			}
		}
		ptr_str = ptr_str->next;
	}
	ft_set_free_env(sh, "?", ft_strdup("0"));
}
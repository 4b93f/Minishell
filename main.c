/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:04:42 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/16 22:16:05 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_actual_path(void)
{
	char	*buf;
	char	*str;
	size_t	size;

	buf = NULL;
	str = NULL;
	size = 10000;
	str = getcwd(buf, size);
	return (str);
}

static char	*argv_to_str(char **arg)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (arg && arg[i])
		str = ft_strjoinfree(str, arg[i++]);
	return (str);
}

void	ft_retval_init(t_sh *sh)
{
	t_env_lst	*ptr;
	char		*var;
	char		*val;

	var = ft_strdup("?");
	if (!var)
		ft_error(MALLOC_ERROR, sh, 0);
	val = ft_strdup("0");
	if (!val)
	{
		free(var);
		ft_error(MALLOC_ERROR, sh, 0);
	}
	ptr = ft_env_lstnew(var, val);
	if (!ptr)
		ft_error(MALLOC_ERROR, sh, 0);
	ft_env_lstadd_back(&sh->env_lst, ptr);
}

char	*del_char(char *s1, int c)
{
	char	*dup;
	int		i;
	int		j;

	dup = NULL;
	i = -1;
	j = -1;
	dup = malloc(sizeof(char *) * strlen(s1));
	if (!dup)
		return (NULL);
	while (s1[++i])
	{
		while (s1[i] == c)
			i++;
		dup[++j] = s1[i];
	}
	dup[++j] = '\0';
	free(s1);
	return (dup);
}

int	parse_input(t_sh *sh)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = -1;
	str = NULL;
	str = calloc(sizeof(char), ft_strlen(sh->input_str) + 1);
	while (sh->input_str[++i])
	{
		if (sh->input_str[i] == '\'')
			while (sh->input_str[++i] && sh->input_str[i] != '\'')
				str[++j] = sh->input_str[i];
		else if (sh->input_str[i] == '\"')
			while (sh->input_str[++i] && sh->input_str[i] != '\"')
				str[++j] = sh->input_str[i];
		else
			str[++j] = sh->input_str[i];
	}
	str[i] = '\0';
	sh->cmd->cmd_str = str;
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_sh		*sh;
	t_history	*history;
	int			ret;
	char		buf[200];

	sh = ft_malloc_sh();
	if (!sh)
		ft_error(MALLOC_ERROR, sh, 0);
	ft_retval_init(sh);
	ft_env_to_lst(env, sh);
	if (!env_lst_finder(sh->env_lst, "PWD"))
		ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(ft_strdup("PWD"), get_actual_path()));
	if (!env_lst_finder(sh->env_lst, "SHLVL"))
		ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(ft_strdup("SHLVL"), ft_strdup("1")));
	else
		ft_set_free_env(sh, "SHLVL", ft_itoa(ft_atoi((char *)env_lst_finder(sh->env_lst, "SHLVL")->content) + 1));
	if (!env_lst_finder(sh->env_lst, "_"))
		ft_env_lstadd_back(&sh->env_lst, ft_env_lstnew(ft_strdup("_"), NULL));
	ret = 1;
	while (ret)
	{
		if (!sh->save_str)
			write(0, "My Minishell1 ~> ", 16);
		//ret = termcap(sh, history);
		//if (!sh->input_str)
		//{
		//    printf("\n");
		//    continue;
		//}
		//ft_historyadd_front(&history, ft_historynew(sh->input_str));
		//ft_print_history(history);
		//printf("{%s}\n", sh->input_str);
		get_all_path(sh);
		ret = 0;
		if ((argc == 1 || ft_strcmp(argv[1], "-c")) && !sh->save_str)
			ret = get_next_line(0, &sh->input_str);
		else if (!sh->save_str)
			sh->input_str = argv_to_str(&argv[2]);
		else
		{
			ret = 1;
			sh->input_str = sh->save_str;
		}
		strtolst(sh);
		parser(sh);
		executor(sh);
		sh_free(sh);
	}
	return (ft_atoi(env_lst_finder(sh->env_lst, "?")->content));
}

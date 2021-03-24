/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:25:48 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/10 21:12:58 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab(char **tab)
{
	int	i;

	i = -1;
	while(tab && tab[++i])
		printf("TAB == {%s}\n", tab[i]);
}

int		ft_isspace(int c)
{
	return (c == 32 || (c > 8 && c < 14));
}

int 	ft_stat(char *filename, t_sh *sh)
{
	struct stat buf;
	if (!ft_strcmp(filename + 2, "."))
		(void)NULL;
	else
	{
		filename = ft_strtrim(sh->cmd->cmd_str, "./");
		filename = ft_strtrim(filename, "/");
	}
	if (stat(filename, &buf) == 0)
	{
		//printf("!\n");
		if (buf.st_mode & S_IFDIR)
			return (ft_error_stat(IS_DIR, sh));
		else if (!(buf.st_mode & S_IXUSR && buf.st_mode & S_IRUSR))
			return (ft_error_stat(PERM, sh));
		else
			return (-1);
	}
	return (-1);
}

int		ft_error_stat(int ret, t_sh *sh)
{
	ft_putstr_fd("minishell: ", sh->cmd->fd_pipe_out);
	static char *error[] = {
		" Permission denied",
		" is a directory"
	};
	if (sh->cmd->cmd_str)
		printf("%s:", sh->cmd->cmd_str);
	printf("%s\n", error[ret]);
	return(ret);
}

void	ft_env_to_lst(char **env, t_sh *sh)
{
	int		i;
	int		equal_pos;
	char	*var;
	char	*value;
	t_env_lst	*new;

	i = -1;
	while (env && env[++i])
	{
		equal_pos = ft_strchr(env[i], '=') - env[i];
		var = ft_substr(env[i], 0, equal_pos - 1);
		if (!var)
			ft_error(MALLOC_ERROR, sh, 0);
		value = ft_substr(env[i], equal_pos, ft_strlen(env[i])); // ne pas equal + 1
		if (!value)
		{
			free(var);
			ft_error(MALLOC_ERROR, sh, 0);
		}
		new = ft_env_lstnew(var, value);
		if (!new)
		{
			free(var);
			free(value);
			ft_error(MALLOC_ERROR, sh, 0);
		}
		ft_env_lstadd_back(&sh->env_lst, new);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 00:46:45 by jsilance          #+#    #+#             */
/*   Updated: 2021/02/09 19:21:19 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	sh_free
**
**	Free the sh struct.
*/

void	sh_free(t_sh *sh)
{
	free(sh->input_str);
	sh->input_str = NULL;
	ft_lstclear(&sh->arg_lst, free);
	sh->arg_lst = NULL;
	ft_cmd_lstclear(&sh->cmd, free);
	sh->cmd = NULL;
	free_tab(sh->all_path);
	sh->all_path = NULL;
}

static int	ft_str_digit(char *str)
{
	while (str && ft_isspace(*str))
		str++;
	if (str && *str == '+')
		str++;
	while (str && *str && !ft_strcmp(str, "-0"))
	{
		if (!ft_isdigit(*str))
			if (*str != 32 && *str != 9)
				return (255);
		str++;
	}
	if (!ft_strcmp(str, "-0"))
		return (0);
	return (1);
}

void	ft_exit(t_cmd_lst *cmd, t_sh *sh)
{
	int	i;
	int	ret;
	char	*str;
	
	str = NULL;
	if (cmd->str)
	{
		cmd->str->content = rm_guim(cmd->str->content);
		str = cmd->str->content;
	}
	ret = ft_atoi(str);
	i = 0;
	if (cmd->str && cmd->str->next)
		ft_error(EXIT_TO_MANY_ARG, sh, 1);
	else if (cmd->str && ft_str_digit(str) == 255)
		ft_error(EXIT_NUM, sh, 255);
	else if (cmd->str && ret >= 0 && (ft_strchr(str, '-') || ft_str_digit(str) != 1))
		ft_error(EXIT_ILLEGAL, sh, 3);
	ft_free_sh(sh);
	exit(ret);
}

/*
** Free all malloc and more	
*/

void		ft_error(int ret, t_sh *sh, int ext)
{
	static char *error[] = {
	"Error with malloc\n",
	"minishell: exit: too many arguments",
	"minishell: exit: Illegal number: ",
	"minishell: exit: numeric argument required: ",
	"minishell: pipe ERROR",
	"minishell: syntax error near unexpected token ';'"
	};
	if (ret > 0)
		printf("%s\n", error[ret]);
	ft_free_sh(sh);
	exit(ext);
}

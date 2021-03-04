/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 00:46:45 by jsilance          #+#    #+#             */
/*   Updated: 2021/02/14 16:59:333 by chly-huc         ###   ########.fr       */
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
	if (str && (*str == '+' || *str == '-'))
		str++;
	if (!ft_strcmp(str, "-0"))
		return (0);
	return (1);
}

static char	*ft_after_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == 32 || str[i] == '\t')
		i++;
	if (str[i])
		return (&str[i]);
	return (NULL);
}

void	ft_exit(t_cmd_lst *cmd, t_sh *sh)
{
	int		i;
	int		ret;
	char	*str;

	str = NULL;
	i = 0;
	ret = 0;
	if (cmd->str)
	{
		cmd->str->content = rm_guim(cmd->str->content);
		str = cmd->str->content;
	}
	if (str && ft_strcmp("-9223372036854775808", str) && (ft_atol(str) || ft_isdigit(str[0]) || ft_isdigit(str[1])))
		ret = ft_atol(str);
	if (str && (ret == -1 || ret == 0) && ft_strlen(str) >= 20 + (str[0] == '-'))
		ft_error_two(str, sh, 255);
	else if ((cmd->str && ret >= 0 && str[0] == '-' && ret < 0))
		ft_error(EXIT_ILLEGAL, sh, ret);
	else if (ft_strcmp("-9223372036854775808", str) != 0 && ((cmd->str && ft_strcmp("9223372036854775807", str) <= 0 && !ret) || ft_after_digit(str)))
		ft_error_two(str, sh, 255);
	else if (cmd->str && cmd->str->next)
		ft_error(EXIT_TO_MANY_ARG, sh, 1);
	ft_free_sh(sh);
	exit(ret);
}

/*
** Free all malloc and more	
*/

int		ft_print_error(int ret, char *str)
{
	static char *error[] = {
	"syntax error near unexpected token",
	"not a valid identifier\n",
	"No such file or directory\n",
	};
	if (str && ret != SYNTAX_ERROR)
		printf(" `%s': ", str);
	if (ret!= -1)
		printf("%s", error[ret]);
	if (str && ret == SYNTAX_ERROR)
		printf(" `%s'\n", str);
	return (1);
}

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
		printf("%s\n", error[ret]);
	ft_free_sh(sh);
	if (ext < 0)
		ext = 255;
	exit(ext);
}

void		ft_error_two(char *str, t_sh *sh, int ext)
{
	static char *error[] = {
	"minishell: exit: ",
	"numeric argument required"
	};
		printf("%s%s: %s\n", error[0], str, error[1]);
	ft_free_sh(sh);
	exit(ext);
}
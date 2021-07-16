/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 00:46:45 by jsilance          #+#    #+#             */
/*   Updated: 2021/07/16 22:34:18 by jsilance         ###   ########.fr       */
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

/*
** Free all malloc and more	
*/

int	ft_print_error(int ret, char *str)
{
	static char	*error[] = {
	"syntax error near unexpected token",
	"not a valid identifier\n",
	"No such file or directory\n",
	};

	if (str && ret != SYNTAX_ERROR)
		printf(" `%s': ", str);
	if (ret != -1)
		printf("%s", error[ret]);
	if (str && ret == SYNTAX_ERROR)
		printf(" `%s'\n", str);
	return (1);
}

void	ft_error(int ret, t_sh *sh, int ext)
{
	static char	*error[] = {
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

void	ft_error_two(char *str, t_sh *sh, int ext)
{
	static char	*error[] = {
	"minishell: exit: ",
	"numeric argument required"
	};

	printf("%s%s: %s\n", error[0], str, error[1]);
	ft_free_sh(sh);
	exit(ext);
}

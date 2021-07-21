/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:15:25 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/21 20:29:08 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H
#include "../env/env.h"
#include "../cmd/cmd.h"
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include "../parser.h"

enum e_boolean
{
	FALSE = 0,
	TRUE
};

typedef struct	s_sh
{
	char *input_str;
	char **all_path;
	

	t_lst_cmd *lst_cmd;
	t_lst_env *lst_env;
}				t_sh;

void str_tolst(char *str, t_sh *sh);
void	ft_print_lst(t_lst_cmd *lst);
t_sh	*ft_malloc_sh(void);
void	env_tolst(char **env, t_sh *sh);
char *env_lstcontent(t_sh *sh, char *str);
char *dollarz(t_sh *sh, char *str);
void env_setup(t_sh *sh, char **env);
void is_quote_open(char *str, int *squote, int *dquote, int i);
t_lst_env	*env_lstfinder(t_lst_env *lst, char *var);
char	*get_actual_path(void);

#endif
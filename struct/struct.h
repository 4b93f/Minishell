/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:15:25 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/20 17:14:57 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H
#include "../env/env.h"
#include "../cmd/cmd.h"
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include "../parser.h"

struct t_lst_env;
struct s_lst_env;

enum e_boolean
{
	FALSE = 0,
	TRUE
};

typedef struct	s_sh
{
	char *input_str;
	char **all_path;
	

	t_lst_cmd *cmd;
	t_lst_env *env;
}				t_sh;

char *str_to_lst(char *str, t_sh *sh);
t_sh	*ft_malloc_sh(void);
void	env_tolst(char **env, t_sh *sh);
char *env_lstcontent(t_sh *sh, char *str);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:20:19 by jsilance          #+#    #+#             */
/*   Updated: 2021/03/26 16:47:17 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft/libft.h"
# include "cmd_cl/ft_cmd_cl.h"
# include "env_cl/ft_env_cl.h"

enum		e_print_error
{
	SYNTAX_ERROR,
	NOT_VALID_ID,
	NO_SUCH_FILE
};

enum		e_token
{
	PIPE = 1,
	S_RIGHT_RED,
	D_RIGHT_RED,
	S_LEFT_RED
};

enum		e_cmd
{
	OTHER = -1,
	EXIT,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV
};

enum		e_error
{
	MALLOC_ERROR,
	EXIT_TO_MANY_ARG,
	EXIT_ILLEGAL,
	EXIT_NUM,
	PIPE_ERROR,
	ECHO_SYNTAX,
};

enum		e_stat
{
	PERM,
	IS_DIR
};

typedef struct	s_parser
{
	int			piped[2];
	t_list		*ptr_lst;
	t_cmd_lst	*ptr_cmd;
}				t_parser;

typedef struct s_history
{
	char *content;
	void *next;
}				t_history;
typedef struct	s_sh
{
	char **all_path;

	char		*input_str;
	char		**exec_env;
	char 		*save_str;
	int			flag_c;
	int			cursor_i;
	int			cursor_j;
	char		*tc_ku;
	char		*tc_kl;
	char		*tc_kr;
	char		*tc_kd;
	int			index_history;
	t_parser	parser;
	t_list		*arg_lst;
	t_cmd_lst	*cmd;
	t_env_lst	*env_lst;
}				t_sh;

#endif
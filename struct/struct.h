/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:15:25 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/12 17:44:37 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H
#include "../cmd/cmd.h"
#include "../env/env.h"
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include "../parser.h"

typedef struct	s_sh
{
	char *input_str;
	char **all_path;

	t_lst_cmd *cmd;
}				t_sh;

#endif
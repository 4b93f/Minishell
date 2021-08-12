/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:52:00 by chly-huc          #+#    #+#             */
/*   Updated: 2021/08/12 16:13:39 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"

//char *next(t_sh *sh)
//{
//	int i;
//	int j;
//	char *tmp;

//	i = 0;
//	j = 0;
//	tmp = NULL;
//	while(sh->input_str[i])
//	{
//		if (sh->input_str[i] && sh->input_str[i + 1] && sh->input_str[i] == '|')
//		{
//			i++;
//			tmp = malloc(sizeof(char*) * (ft_strlen(sh->input_str) - i));
//			while(sh->input_str[i])
//				tmp[j++] = sh->input_str[i++];
//			tmp[j] = '\0';
//			return (tmp);
//		}
//		i++;
//	}
//	return(tmp);
//}

void	ft_reset(t_sh *sh)
{
	if(sh->fd_in != -1)
		close(sh->fd_in);
	if(sh->fd_out != -1)
		close(sh->fd_out);
	sh->fd_in = -1;
	sh->fd_out = -1;
	dup2(sh->fd_backup[0], 0);
	dup2(sh->fd_backup[1], 1);
}

void sh_free(t_sh *sh)
{
	cmd_lstclear(&sh->lst_cmd, free);
	free(sh->free_ptr);
	free_tab(sh->all_path);
	free(sh->input_str);
	//free(sh->dup);
	sh->all_path = NULL;
	sh->flag_n = 0;
	dup2(sh->fd_backup[0], 0);
	dup2(sh->fd_backup[1], 1);
	sh->ptr_cmd = sh->lst_cmd;
	if (sh->fd_in != 0)
		close(sh->fd_in);
	if (sh->fd_out != 1)
		close(sh->fd_out);
	sh->fd_in = 0;
	sh->fd_out = 1;
	sh->block_cmd = 0;
}
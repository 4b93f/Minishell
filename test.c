/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:23:44 by chly-huc          #+#    #+#             */
/*   Updated: 2021/03/20 21:09:57 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <termios.h>
/*
int get_pos(int *y, int *x) {

	char buf[30]={0};
	int ret;
	int i;
	int pow;
	char ch;

	*y = 0; *x = 0;

	struct termios term;
	struct termios restore;

	tcgetattr(0, &term);
	tcgetattr(0, &restore);
	term.c_lflag &= ~(ICANON|ECHO);
	tcsetattr(0, TCSANOW, &term);

	write(1, "\033[6n", 4);
	i = 0;
	while (ch != 'R')
	{
		ret = read(0, &ch, 1);
		if (!ret) 
		{
			tcsetattr(0, TCSANOW, &restore);
			return 1;
		}
		buf[i] = ch;
		i++;
		//printf("buf[%d]={%c} %d\n", i, ch, ch);
		//printf("{%s}\n", buf);
	}

	if (i < 2) {
		tcsetattr(0, TCSANOW, &restore);
		//printf("i < 2\n");
		return(1);
	}
	i = 1;
	while(buf[++i] != ';')
		*y = *y * 10 + (buf[i] - '0');
	while(buf[++i] != 'R')
		*x = *x * 10 + (buf[i] - '0');
	tcsetattr(0, TCSANOW, &restore);
	return 0;
}
*/
int main() 
{
	char *buf;
	buf = calloc(sizeof(char), 30);
	buf[5] = '1';
	
//	int x = 0, y = 0;
//	get_pos(&y, &x);
//	printf("x:%d, y:%d\n", x, y);
//	return 0;
}
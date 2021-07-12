#ifndef WORK_PARSER_H
#define WORK_PARSER_H
#include "struct/struct.h"

#define BUFF_MAX 1024
# define NONE 0
# define QUOTE 1
# define D_QUOTE 2

//char    *ft_strjoin(char const *s1, char const *s2);

typedef struct s_parsing
{
	int quote;
	char buff[1024];
	int	pos;
	char *final;
}				t_parsing;
typedef struct s_cmd
{
	char *cmd;
	char **arg;
	char sep;
}				t_cmd;

#endif

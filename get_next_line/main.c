#include "get_next_line.h"
#include <fcntl.h>

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;

	get_next_line(0, &line);
	//printf("%s\n",line);
	free(line);
}
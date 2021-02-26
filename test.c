#include "minishell.h"

char *fulltrim(char *s1, int c)
{
	char *dup;
	int i;
	int j;
	int first;

	dup = NULL;
	i = -1;
	j = -1;
	dup = malloc(sizeof(char*) * strlen(s1));
	if (!dup)
		return (NULL);
	while (s1[++i])
	{
		first = 0;
		while (s1[i] == c)
		{
			i++;
			first++;
		}
		if (first > 0)
			dup[++j] = c;
		dup[++j] = s1[i];
	}
	dup[j] = c;
	dup[++j] = '\0';
	free(s1);
	return (dup);
}

int main()
{
	char *str = strdup("ok    lourd         ok      ");
	char *dup;
	dup = fulltrim(str, ' ');
	printf("|%s|\n", dup);
	return (0);
}
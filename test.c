#include "minishell.h"

char *ft_backslash(char *s1)
{
	int i;
	int j;
	char *s2;

	i = -1;
	j = 0;
	if (!s1)
		return (NULL);
	s2 = malloc(sizeof(char*) * strlen(s1));
	if (!s2)
		return (NULL);
	while (s1[++i])
	{
		if (s1[i] == '\\')
			i++;
		if (s1[i])
			s2[j] = s1[i];
		j++;
	}
	return (s2);
}

int main()
{
	char *str = strdup("ok\\\\lourd\\\\");
	str = ft_backslash(str);
	printf("|%s|\n", str);
	return (0);
}
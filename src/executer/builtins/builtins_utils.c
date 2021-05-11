#include "minishell.h"

int	ft_strncmpsep(char *s1, char *s2, unsigned int n, char sep)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != sep) && i < n)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (s2[i] != sep)
		return (-1);
	return (0);
}

int	ft_strlen_sep(char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

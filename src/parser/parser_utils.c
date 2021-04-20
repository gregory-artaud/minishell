#include "minishell.h"

static	char	*ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*my_strdup(char *src, int n)
{
	char *str;

	str = (char*)malloc(sizeof(*str) * n + 1);
	if (str == NULL)
		return (0);
	ft_strncpy(str, src, n);
	return (str);
}

int	ft_strlen_sp(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != c)
		i++;
	return (i);
}

void	ft_errorzsh(char *cmd)
{
	printf("zsh: command not found: %s\n", cmd);
}
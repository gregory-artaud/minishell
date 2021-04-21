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

int	ft_verif_builtin(char *builtin, char *charset)
{
	int		len;
	char	c;

	if (charset == NULL)
		c = ';';
	else
		c = *charset;
	len = ft_strlen_sp(builtin, c);
	if (ft_strncmp("echo", builtin, len) != 0 && ft_strncmp("cd", builtin, len)
		!= 0 && ft_strncmp("pwd", builtin, len) != 0
		&& ft_strncmp("export", builtin, len) != 0
		&& ft_strncmp("unset", builtin, len) != 0
		&& ft_strncmp("env", builtin, len) != 0
		&& ft_strncmp("exit", builtin, len) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

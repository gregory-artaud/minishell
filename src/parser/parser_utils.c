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

int	my_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
    int             result;

	i = 0;
	while (s1[i] && ((s1[i] == s2[i] || (((unsigned char)s1[i])
        - ((unsigned char)s2[i])) == 32)) && (i < n - 1))
		i++;
    if (s1[i + 1] != 0 || s2[i + 1] != 0)
        return (-1);
    result = ((unsigned char)s1[i]) - ((unsigned char)s2[i]);
	if (result == 32)
        result = 0;
	if (n)
		return (result);
	return (0);
}

int	ft_verif_builtin(char *builtin)
{
	int		len;

	len = ft_strlen(builtin);
	if (my_strncmp("echo", builtin, len) != 0 && my_strncmp("cd", builtin, len)
		!= 0 && my_strncmp("pwd", builtin, len) != 0
		&& my_strncmp("export", builtin, len) != 0
		&& my_strncmp("unset", builtin, len) != 0
		&& my_strncmp("env", builtin, len) != 0
		&& my_strncmp("exit", builtin, len) != 0)
    {
        if (ft_strncmp(builtin, "./", 2) == 0)
            return (EXIT_SUCCESS);
        else
		    return (EXIT_FAILURE);
    }
	return (EXIT_SUCCESS);
}

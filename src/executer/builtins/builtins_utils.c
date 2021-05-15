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

int	create_file_redirect(t_tree *root)
{
	char	**redirect;
	int		i;
	int		fd;

	redirect = root->content;
	i = 0;
	while (redirect[i])
	{
		if (ft_strncmp(redirect[i], ">", 1) && ft_strncmp(redirect[i], ">>", 2))
		{
			i++;
			fd = open(redirect[i], O_RDWR);
			if (fd < 0)
			{
				printf("minishell: %s: %s\n", redirect[i], strerror(errno));
				return (fd);
			}
			fd = 1;
		}
		else if (!ft_strncmp(redirect[i], ">>", 2))
		{
			i++;
			fd = open(redirect[i], O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
			if (fd < 0)
				printf("minishell: %s: %s\n", redirect[i], strerror(errno));
		}
		else
		{
			i++;
			fd = open(redirect[i], O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
			if (fd < 0)
				printf("minishell: %s: %s\n", redirect[i], strerror(errno));
		}
		i++;
	}
	return (fd);
}

#include "minishell.h"

char	*free_not_env(char *var)
{
	char *s1;
	char *s2;
	char *s3;

	s1 = ft_substr(var, 0, ft_strlen_sep(var, '=') - 1);
	s2 = ft_substr(var, ft_strlen_sep(var, '='), ft_strlen(var));
	s3 = ft_strjoin(s1, s2);
	free(var);
	free(s1);
	free(s2);
	return (s3);
}

char	*free_env_join(char *dst, char *str)
{
	char *s1;
	char *s2;

	s1 = ft_substr(str, ft_strlen_sep(str, '=') + 1, ft_strlen(str));
	s2 = ft_strjoin(dst, s1);
	free(s1);
	free(dst);
	return (s2);
}

char	*free_env_join_sep(char *str)
{
	char *s1;

	s1 = ft_strjoin(str, "=");
	free(str);
	return (s1);
}

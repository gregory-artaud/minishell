#include "minishell.h"

char	brw_line(char *line)
{
	int i;

	i = 0;
	while(line[i] && line[i] != ';' && line[i] != '|')
		i++;
	return (line[i]);
}

char	*clear_isspace(char *line, char c)
{
	int	i;

	i = ft_strlen_sp(line, c);
	while (i--)
		(line)++;
	while (*line == '\t' || *line == '\n' || *line == '\v' ||
		*line == '\f' || *line == '\r' || *line == ' ')
		(line)++;
	return (line);
}

int	ft_verif_builtin(char *builtin, char c)
{
	int	len;

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

int	fill_tree(char c, t_shell *sh)
{
	char	*charset;
	t_tree	*root;
	char	*arg;
	char	*line;
	t_tree	*begin;

	line = sh->cmd;
	if (c)
	{
		charset = &c;
		charset[1] = '\0';
		root = ft_tr_new(charset);
	}
	else
	{
		arg = my_strdup(line, ft_strlen_sp(line, c));
		if (ft_verif_builtin(arg, c))
			ft_errorzsh(arg);
		root = ft_tr_new(arg);
	}
	begin = root;
	line = clear_isspace(line, c);
	while (*line)
	{
		arg = my_strdup(line, ft_strlen_sp(line, c));
		ft_tr_addleft(root, ft_tr_new(arg));
		root = root->branches->content;
		line = clear_isspace(line, c);
	}
	printf("%s\n", root->content);
	// if (c)
	// {
	// 	charset = &c;
	// 	charset[1] = '\0';
	// 	root = ft_tr_new(charset);
	// 	begin = root;
	// 	while (*line != c)
	// 	{
	// 		builtin = my_strdup(line, ft_strlen_sp(line, c));
	// 		ft_tr_addleft(root, ft_tr_new(builtin));
	// 		root = root->branches->content;
	// 		line = clear_isspace(line, c);
	// 	}
	// }
	return (1);
}

int	parser(t_shell *sh)
{
	char	c;

	c = brw_line(sh->cmd);
	fill_tree(c, sh);
	return (EXIT_SUCCESS);
}

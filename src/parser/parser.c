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

int	fill_tree(t_shell sh)
{
	t_tree	*root;
	int		nb_sep;

	root = ft_tr_new(NULL);
	nb_sep = fill_separator(sh, root);
	while (nb_sep--)
	{
		if (fill_cmd(&sh, root))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parser(t_shell *sh)
{
	char	c;

	c = brw_line(sh->cmd);
	fill_tree(*sh);
	return (EXIT_SUCCESS);
}

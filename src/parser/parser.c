#include "minishell.h"

char	brw_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ';' && line[i] != '|')
		i++;
	return (line[i]);
}

char	*clear_isspace(char *line, char c)
{
	int	i;

	i = ft_strlen_sp(line, c);
	while (i--)
		(line)++;
	while (*line == '\t' || *line == '\n' || *line == '\v'
		|| *line == '\f' || *line == '\r' || *line == ' ')
		(line)++;
	return (line);
}

int	count_separator(t_shell sh)
{
	t_token	*token;
	int		i;

	i = 0;
	while (sh.tokens)
	{
		token = sh.tokens->content;
		if (token->type == SEPARATOR)
			i++;
		sh.tokens = sh.tokens->next;
	}
	return (i);
}

void	print_cmd(t_tree *tree)
{
	char	*test;
	char	*test2;
	t_tree	*left;
	t_tree	*right;
	t_list	*next;

	left = ft_tr_leftchild(tree);
	left = tree->branches->content;
	left = left->branches->content;
	// printf("test\n");
	test = *(char **)(left->content);
	printf("content : %s\n", test);
	next = tree->branches->next;
	right = next->content;
	right = right->branches->content;
	// right = right->branches->content;
	test2 = *(char **)(right->content);
	printf("content 2 : %s\n", test2);
	// begin = tree;
	// tree = tree->branches->content;
	// printf("tree : %s\n", tree->content);
	// tree = tree->branches->content;
	// printf("%s\n", test);
	// tree = begin;
	// tree = tree->branches->content;
	// test = *(char **)(tree->content);
	// printf("%s\n", test);
}

char	**ft_fill_tab_sep(t_shell sh)
{
	t_token	*token;
	char	**tab;
	int		i;
	int		j;

	i = count_separator(sh);
	tab = malloc(sizeof(char *) * i);
	j = 0;
	while (sh.tokens)
	{
		token = sh.tokens->content;
		if (token->type == SEPARATOR)
		{
			tab[j] = malloc(sizeof(char) * 2);
			tab[j] = token->value;
			j++;
		}
		sh.tokens = sh.tokens->next;
	}
	return (tab);
}

int	ft_count_exec(t_shell sh)
{
	t_token	*token;
	int		i;

	i = 0;
	while (sh.tokens)
	{
		token = sh.tokens->content;
		if (token->type == EXECUTABLE)
			i++;
		sh.tokens = sh.tokens->next;
	}
	return (i);
}

int	fill_tree(t_shell sh)
{
	t_tree	*root;
	t_tree	*begin;
	int		nb_sep;
	char	**tab_sep;
	int		i;

	i = 0;
	root = ft_tr_new(NULL);
	begin = root;
	tab_sep = ft_fill_tab_sep(sh);
	nb_sep = ft_count_exec(sh);
	while (nb_sep--)
	{
		if (fill_cmd(&sh, root, tab_sep, i))
			return (EXIT_FAILURE);
		i++;
	}
	// print_cmd(begin);
	return (EXIT_SUCCESS);
}

int	parser(t_shell *sh)
{
	char	c;

	c = brw_line(sh->cmd);
	fill_tree(*sh);
	return (EXIT_SUCCESS);
}

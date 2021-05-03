#include "minishell.h"

char	brw_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ';' && line[i] != '|')
		i++;
	return (line[i]);
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
	right = right->branches->content;
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

void    ft_brw_token(t_shell *sh, int *nb_sep)
{
    t_token *token;

    if (sh->tokens)
        token = sh->tokens->content;
    while (sh->tokens && token->type != SEPARATOR)
    {
        sh->tokens = sh->tokens->next;
        if (sh->tokens)
            token = sh->tokens->content;
        else 
            *nb_sep = 0;
    }
}

t_tree	*fill_tree(t_shell sh)
{
	t_tree	*root;
	t_tree	*begin;
	int		nb_sep;

	root = ft_tr_new(NULL);
	begin = root;
	nb_sep = ft_count_exec(sh);
	while (nb_sep--)
		if (fill_cmd(&sh, root))
			ft_brw_token(&sh, &nb_sep);
	return (begin);
}

int	parser(t_shell *sh)
{
	char	c;

	c = brw_line(sh->cmd);
	sh->ast = fill_tree(*sh);
	return (EXIT_SUCCESS);
}

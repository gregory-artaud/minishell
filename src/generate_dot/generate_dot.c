#include "minishell.h"

/*
** TESTS
*/
// echo lol oui >> tata < toto ; cd dossier | commande | dodo

void	write_id(t_tree *ast, int fd)
{
	char	*id;

	id = ft_itoa_base((long long)ast, "0123456789abcdef");
	ft_putstr_fd("\t\"", fd);
	ft_putstr_fd(id, fd);
	ft_putstr_fd("\" ", fd);
}

void	write_tree(int fd, t_tree *ast)
{
	t_tree	*child;

	if (ft_tr_isleaf(ast) && !ast->parent)
	{
		write_id(ast, fd);
		return ;
	}
	child = ft_tr_leftchild(ast);
	while (child)
	{
		write_id(ast, fd);
		ft_putstr_fd(" -- ", fd);
		write_id(child, fd);
		ft_putstr_fd("\n", fd);
		child = ft_tr_next_sibling(child);
	}
	child = ft_tr_leftchild(ast);
	while (child)
	{
		write_tree(fd, child);
		child = ft_tr_next_sibling(child);
	}
}

void	write_label(t_tree *ast, int fd)
{
	int	i;

	i = 0;
	write_id(ast, fd);
	ft_putstr_fd("[label=\"", fd);
	if (ast->type == EXECUTABLE || ast->type == SEPARATOR)
		ft_putstr_fd(ast->content, fd);
	else if (ast->type == ARGUMENT || ast->type == REDIRECT)
	{
		ft_putstr_fd("[", fd);
		while (i < ast->size)
		{
			if (i != 0)
				ft_putstr_fd(",", fd);
			ft_putstr_fd(" '", fd);
			ft_putstr_fd(((char **)ast->content)[i], fd);
			ft_putstr_fd("' ", fd);
			i++;
		}
		ft_putstr_fd("]", fd);
	}
	ft_putstr_fd("\"]\n", fd);
}

void	parse_labels(t_tree *ast, int fd)
{
	t_tree	*child;

	write_label(ast, fd);
	child = ft_tr_leftchild(ast);
	while (child)
	{
		parse_labels(child, fd);
		child = ft_tr_next_sibling(child);
	}
}

void	generate_dot(t_tree *ast)
{
	int	fd;

	fd = open("ast.dot", O_RDWR | O_CREAT, 0777);
	if (fd == -1)
		return ;
	g_sh->i = 0;
	ft_putstr_fd("graph ast {\n\tforcelabels=true\n", fd);
	parse_labels(ast, fd);
	write_tree(fd, ast);
	ft_putstr_fd("}", fd);
}

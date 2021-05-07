#include "minishell.h"

void	clear_arg(t_tree *next)
{
	char	**tab;
	int		i;

	tab = (char **)(next->content);
	if (next->type == ARGUMENT)
	{
		i = 0;
		while (i < next->size)
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	clear_redirect(t_tree *root)
{
	char	**tab;
	t_tree	*redir;
	int		i;

	redir = root->branches->next->content;
	tab = (char **)(redir->content);
	if (redir->type == REDIRECT || redir->type == FILE_PATH)
	{
		i = 2;
		while (i--)
			free(tab[i]);
		free(tab);
	}
}

void	clear_ast(t_tree **tree)
{
	t_tree	*next;
	t_list	*new;

	if (!(*tree))
		return ;
	clear_arg(*tree);
	if ((*tree)->branches)
	{
		next = (*tree)->branches->content;
		clear_ast(&next);
		if ((*tree)->branches->next)
		{
			clear_redirect(*tree);
			new = (*tree)->branches->next;
			next = new->content;
			free(new);
			clear_ast(&next);
		}
		free((*tree)->branches);
	}
	free(*tree);
	*tree = NULL;
}

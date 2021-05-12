#include "minishell.h"

void	clear_arg(t_tree *next)
{
	char	**tableau;
	int		i;

	tableau = (char **)(next->content);
	if (next->type == ARGUMENT || next->type == REDIRECT)
	{
		i = 0;
		while (i < next->size)
		{
			free(tableau[i]);
			tableau[i] = NULL;
			i++;
		}
		free(tableau);
		tableau = NULL;
	}
}

void	clear_redirect(t_tree *root)
{
	char	**tableau;
	t_tree	*redir;
	int		i;

	redir = root->branches->next->content;
	tableau = (char **)(redir->content);
	if (redir->type == REDIRECT)
	{
		i = 0;
		while (i < redir->size)
		{
			free(tableau[i]);
			tableau[i] = NULL;
			i++;
		}
		free(tableau);
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
			// clear_redirect(*tree);
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

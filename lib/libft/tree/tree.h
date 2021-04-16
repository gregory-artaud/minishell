#ifndef TREE_H
# define TREE_H

# include "../libft.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_tree
{
	void	*content;
	t_list	*branches;
}			t_tree;

/*
** tree
*/
t_tree	*ft_tr_new(void *content);
void	ft_tr_addleft(t_tree *root, t_tree *left);
void	ft_tr_addright(t_tree *root, t_tree *right);
int		ft_tr_isleaf(t_tree *tr);
int		ft_tr_brsize(t_tree *tr);

/*
** list
*/
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
#endif

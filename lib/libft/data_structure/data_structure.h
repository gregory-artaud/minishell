#ifndef DATA_STRUCTURE_H
# define DATA_STRUCTURE_H

# include "../libft.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_tree
{
	void			*content;
	int				type;
	struct s_tree	*parent;
	t_list			*branches;
	int				size;
}					t_tree;

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*previous;
}					t_dlist;

/*
** tree
*/
t_tree	*ft_tr_new(void *content, int type, int size);
void	ft_tr_addleft(t_tree *root, t_tree *left);
void	ft_tr_addright(t_tree *root, t_tree *right);
int		ft_tr_isleaf(t_tree *tr);
int		ft_tr_brsize(t_tree *tr);
t_tree	*ft_tr_leftchild(t_tree *tr);
t_tree	*ft_tr_next_sibling(t_tree *tr);

/*
** list
*/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
			void (*del)(void *));

/*
** dlist
*/
t_dlist	*ft_dlstnew(void *content);
void	ft_dlstadd_front(t_dlist **alst, t_dlist *new);
int		ft_dlstsize(t_dlist *lst);
t_dlist	*ft_dlstlast(t_dlist *lst);
void	ft_dlstadd_back(t_dlist **alst, t_dlist *new);
void	ft_dlstdelone(t_dlist *lst, void (*del)(void *));
void	ft_dlstclear(t_dlist **lst, void (*del)(void *));
#endif

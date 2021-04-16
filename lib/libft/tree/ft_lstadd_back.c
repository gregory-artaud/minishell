/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 12:01:49 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/15 14:59:18 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (!*alst)
		*alst = new;
	else
		ft_lstlast(*alst)->next = new;
	new->next = NULL;
	return ;
}

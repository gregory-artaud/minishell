/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimon <tsimon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 12:01:49 by gartaud           #+#    #+#             */
/*   Updated: 2021/05/07 11:38:37 by tsimon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*maillon;

	if (*alst == 0)
		*alst = new;
	else
	{
		maillon = *alst;
		while (maillon->next != 0)
			maillon = maillon->next;
		maillon->next = new;
	}
}

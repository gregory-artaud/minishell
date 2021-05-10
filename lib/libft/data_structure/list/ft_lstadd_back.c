/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 12:01:49 by gartaud           #+#    #+#             */
/*   Updated: 2021/05/09 14:51:43 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"

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

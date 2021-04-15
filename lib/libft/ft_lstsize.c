/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 11:51:42 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/02 10:47:15 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	unsigned int	i;
	t_list			*current;

	if (!lst)
		return (0);
	current = lst->next;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i + 1);
}

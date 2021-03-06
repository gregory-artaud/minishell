/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:22:47 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/02 11:32:20 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arrlen(char **array)
{
	int		i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

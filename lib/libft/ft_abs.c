/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:26:16 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/02 11:32:56 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_abs(long long x)
{
	long long	cpy;

	cpy = x;
	if (cpy < 0)
		cpy = -cpy;
	return ((unsigned long long)cpy);
}

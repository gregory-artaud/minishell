/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:10:16 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/02 10:45:31 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

	if (!dest && !src)
		return (0);
	d = (char *)dest;
	s = (char *)src;
	i = -1;
	if (s < d)
		while ((int)(--n) >= 0)
			d[n] = s[n];
	else
		while (++i < n)
			d[i] = s[i];
	return (dest);
}

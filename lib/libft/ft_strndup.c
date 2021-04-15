/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:30:51 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/02 09:51:53 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char const *s, size_t n)
{
	char	*res;

	res = malloc(sizeof(char) * n + 1);
	if (!res)
		return (0);
	ft_memcpy(res, s, n);
	res[n] = 0;
	return (res);
}

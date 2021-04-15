/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 07:48:25 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/02 09:44:23 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_minimum(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	slen;
	unsigned int	sublen;
	unsigned int	i;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start >= slen)
		start = slen;
	sublen = ft_minimum(slen, len);
	substr = (char *)malloc(sizeof(char) * (sublen + 1));
	if (!substr)
		return (0);
	i = -1;
	while (++i < sublen)
		substr[i] = s[i + start];
	substr[i] = 0;
	return (substr);
}

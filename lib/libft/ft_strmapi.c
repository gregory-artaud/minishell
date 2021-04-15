/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 11:44:29 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/02 09:54:53 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	i;

	if (!s)
		return (0);
	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (0);
	i = -1;
	while (s[++i])
		res[i] = f(i, s[i]);
	res[i] = 0;
	return (res);
}

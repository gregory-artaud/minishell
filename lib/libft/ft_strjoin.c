/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 07:58:33 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/02 09:56:02 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*concat;
	size_t			s1_len;
	size_t			s2_len;
	unsigned int	i;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	concat = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!concat)
		return (0);
	i = -1;
	while (++i < s1_len + s2_len)
	{
		if (i < s1_len)
			concat[i] = s1[i];
		else
			concat[i] = s2[i - s1_len];
	}
	concat[i] = 0;
	return (concat);
}

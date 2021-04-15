/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:30:04 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/02 09:59:17 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*new_string;
	unsigned int	i;

	new_string = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_string)
		return (0);
	i = -1;
	while (s[++i])
		new_string[i] = s[i];
	new_string[i] = 0;
	return (new_string);
}

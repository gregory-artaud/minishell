/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isspace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 22:07:36 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/17 22:08:43 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isspace(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!ft_isspace(s[i]))
			return (0);
	return (1);
}
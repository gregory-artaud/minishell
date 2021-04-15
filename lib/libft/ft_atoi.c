/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 11:59:55 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/02 11:32:05 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

int	ft_atoi(const char *s)
{
	unsigned int	i;
	int				sgn;
	long long		res;

	i = 0;
	sgn = 1;
	res = 0;
	while (ft_isspace(s[i]))
		i++;
	if ((s[i] == '-') || (s[i] == '+'))
	{
		if (s[i] == '-')
			sgn = -1;
		i++;
	}
	while (s[i] && ft_isdigit(s[i]))
	{
		res = res * 10 + s[i++] - '0';
		if (res * sgn > INT_MAX)
			return (-1);
		else if (res * sgn < INT_MIN)
			return (0);
	}
	return (res * sgn);
}

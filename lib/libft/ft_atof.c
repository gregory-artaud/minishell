/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:45:10 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/02 11:32:12 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *s)
{
	double	floor;
	double	decimal;
	double	m;
	char	*start;

	start = s;
	floor = (double)ft_atoi(s);
	s = ft_strchr(s, '.');
	if (!s)
		return (floor);
	s++;
	if (*s && !ft_isdigit(*s))
		return (floor);
	m = 1.0 / 10.0;
	decimal = 0.0;
	while (*s && ft_isdigit(*s))
	{
		decimal += (*s++ - '0') * m;
		m /= 10.0;
	}
	if (*start == '-')
		return (floor - decimal);
	return (floor + decimal);
}

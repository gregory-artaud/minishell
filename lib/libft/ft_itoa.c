/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 10:18:54 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/02 11:04:16 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	unsigned int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		is_neg;
	int		num_len;
	int		next_digit;

	is_neg = (n < 0);
	num_len = count_digits(n) + is_neg;
	res = malloc(sizeof(char) * (num_len + 1));
	if (!res)
		return (0);
	res[num_len--] = 0;
	if (is_neg)
		res[0] = '-';
	while (num_len >= is_neg)
	{
		next_digit = n % 10;
		if (next_digit < 0)
			next_digit *= -1;
		res[num_len--] = next_digit + '0';
		n /= 10;
	}
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 10:16:02 by gartaud           #+#    #+#             */
/*   Updated: 2021/05/07 15:07:28 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getchar(void)
{
	unsigned char	c;
	int				ret;

	ret = read(STDIN_FILENO, &c, 1);
	if (!ret)
		return (-1);
	return ((int)c);
}

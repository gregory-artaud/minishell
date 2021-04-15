/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 12:19:45 by gartaud           #+#    #+#             */
/*   Updated: 2020/11/18 17:04:43 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		c;
	long int	n_cp;

	n_cp = (long int)n;
	if (n_cp < 0)
	{
		n_cp *= -1;
		write(fd, "-", 1);
	}
	if (n_cp / 10)
		ft_putnbr_fd(n_cp / 10, fd);
	c = (n_cp % 10) + '0';
	write(fd, &c, 1);
	return ;
}

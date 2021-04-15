/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 14:34:29 by gregory           #+#    #+#             */
/*   Updated: 2021/01/14 13:11:03 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

int		get_next_line(int fd, char **line);
char	*ft_remainder(char *str);
int		ft_is_in(char *str, char c);
char	*ft_strcdup(char *str, char c);
char	*ft_append(char *s1, char *s2);

#endif

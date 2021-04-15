/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 14:34:17 by gregory           #+#    #+#             */
/*   Updated: 2021/04/02 09:36:12 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_remainder(char *str)
{
	int		i;
	int		j;
	char	*res;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i])
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	res = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!res)
		return (0);
	j = -1;
	while (str[i + ++j])
		res[j] = str[i + j];
	res[j] = 0;
	free(str);
	return (res);
}

int	ft_is_in(char *str, char c)
{
	int		i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

char	*ft_strcdup(char *s, char c)
{
	char	*res;
	int		res_ln;
	int		i;

	if (!s)
		return (0);
	res_ln = ft_is_in(s, c);
	if (res_ln == -1)
		res_ln = ft_strlen(s);
	res = malloc(sizeof(char) * (res_ln + 1));
	if (!res)
		return (0);
	i = -1;
	while (++i < res_ln)
		res[i] = s[i];
	res[i] = 0;
	return (res);
}

char	*ft_append(char *s1, char *s2)
{
	char	*res;
	int		res_ln;
	int		s1_ln;
	int		i;

	if (!s2 && !s1)
		return (0);
	s1_ln = ft_strlen(s1);
	res_ln = s1_ln + ft_strlen(s2);
	res = malloc(sizeof(char) * (res_ln + 1));
	if (!res)
		return (0);
	i = -1;
	while (++i < res_ln)
	{
		if (i < s1_ln)
			res[i] = s1[i];
		else
			res[i] = s2[i - s1_ln];
	}
	res[i] = 0;
	free(s1);
	return (res);
}

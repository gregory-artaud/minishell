/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cs_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 13:08:01 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/02 11:05:56 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_is_in_tab(char c, char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			return (i);
		i++;
		str++;
	}
	return (-1);
}

int	ft_count_words(char *str, char *charset)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (ft_is_in_tab(str[i], charset) != -1))
			i++;
		if (str[i])
			res++;
		while (str[i] && (ft_is_in_tab(str[i], charset) == -1))
			i++;
	}
	return (res);
}

char	*ft_strndup(char *str, int n)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (n + 1));
	i = 0;
	while (i < n)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	**ft_cs_split(char *str, char *charset)
{
	char	**res;
	int		i;
	int		j;
	int		word_start_i;

	res = malloc(sizeof(char *) * (ft_count_words(str, charset) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	word_start_i = 0;
	while (str[i])
	{
		while (ft_is_in_tab(str[i], charset) != -1)
			i++;
		word_start_i = i;
		while ((str[i]) && (ft_is_in_tab(str[i], charset) == -1))
			i++;
		if (i > word_start_i)
			res[j++] = ft_strndup(str + word_start_i, i - word_start_i);
	}
	res[j] = NULL;
	return (res);
}

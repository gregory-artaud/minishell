/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 13:57:05 by gartaud           #+#    #+#             */
/*   Updated: 2021/05/07 16:25:19 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include "gnl/get_next_line.h"
# include "tree/tree.h"
# define LFT_LEFT 0
# define LFT_RIGHT 1
# define SPACES " \n\t\r\v\f"

/*
** Part one functions (libc functions)
*/
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlen(const char *s);
void				ft_bzero(void *s, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s);
/*
** Part two functions (additional functions)
*/
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strndup(char const *s, size_t n);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
/*
** Personal fucntions
*/
unsigned long long	ft_abs(long long x);
char				*ft_itoa_base(long long nbr, char *base);
void				ft_strinsert(char **s, int i, char c);
char				**ft_cs_split(char const *s, char *charset);
void				ft_free_strarray(char **array);
int					ft_arrlen(char **array);
double				ft_atof(char *s);
int					ft_isspace(char c);
int					ft_is_int(char *s);
int					ft_is_double(char *s);
int					ft_min(int a, int b);
int					ft_getchar(void);
int					ft_str_isspace(char *s);
char				*ft_strncpy(char *dest, char *src, int n);
void				ft_putchar(char c);
#endif

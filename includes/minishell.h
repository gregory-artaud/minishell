/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 09:25:06 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/15 09:48:47 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_shell
{
	char		*dir;
}				t_shell;

void	init_shell(t_shell *sh, int argc, char **env);
/*
** parsing/
*/
void	read_cmd(t_shell *sh);
/*
** execution/
*/
void	exec_cmd(t_shell *sh);

#endif

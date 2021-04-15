/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 09:21:16 by gartaud           #+#    #+#             */
/*   Updated: 2021/04/15 09:41:39 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **env)
{
	t_shell	sh;

	init_shell(&sh, argc, env);
	while (1)
	{
		printf("%s", sh.dir);
		read_cmd(&sh);
		exec_cmd(&sh);
	}
	return (EXIT_SUCCESS);
}

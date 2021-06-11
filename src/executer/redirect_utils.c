#include "minishell.h"

int	create_file(char *file, int mode)
{
	int	fd;

	fd = open(file, O_RDONLY | O_CREAT | mode, 0644);
	if (fd == -1)
	{
		printf("minishell: %s: %s\n", file, strerror(errno));
		return (1);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	check_input(char **files, int i)
{
	int	error;

	error = 0;
	if (!ft_memcmp(files[i], REDIRECT_INPUT_TOKEN, R_I_T_LEN + 1))
		error = !does_file_exists(files[i + 1]);
	if (error)
		printf("minishell: %s: %s\n", files[i + 1], strerror(errno));
	return (error);
}

int	check_append(char **files, int i)
{
	int	error;

	if (ft_memcmp(files[i], REDIRECT_OUTPUT_APPEND_TOKEN, R_O_A_T_LEN + 1))
		return (0);
	error = create_file(files[i + 1], 0);
	return (error);
}

int	check_output(char **files, int i)
{
	int	error;

	if (ft_memcmp(files[i], REDIRECT_OUTPUT_TOKEN, R_O_T_LEN + 1))
		return (0);
	error = create_file(files[i + 1], O_TRUNC);
	return (error);
}

int	create_files(t_tree *tr)
{
	char	**files;
	int		i;
	int		error;

	if (!tr)
		return (EXIT_SUCCESS);
	files = (char **)tr->content;
	i = 0;
	while (i < tr->size)
	{
		error = 0;
		error = check_input(files, i);
		if (error)
			return (error);
		error = check_append(files, i);
		if (error)
			return (error);
		error = check_output(files, i);
		if (error)
			return (error);
		i += 2;
	}
	return (EXIT_SUCCESS);
}

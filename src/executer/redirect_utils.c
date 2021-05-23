#include "minishell.h"

int		create_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY | O_CREAT, 0777);
	if (fd == -1)
		return (EXE_ERR_FILE_CREATION);
	close(fd);
	return (EXIT_SUCCESS);
}

int		create_files(t_tree *tr)
{
	char	**files;
	int		i;
	char	*current;
	int		error;

	files = (char **)tr->content;
	i = 0;
	while (i < tr->size)
	{
		error = 0;
		current = files[i];
		if (ft_memcmp(current, REDIRECT_INPUT_TOKEN, R_I_T_LEN + 1))
			error = create_file(files[i + 1]);
		if (error)
			return (error);
		i += 2;;
	}
	return (EXIT_SUCCESS);
}

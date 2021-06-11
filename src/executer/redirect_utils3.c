#include "minishell.h"

int	does_file_exists(char *f)
{
	int	fd;

	fd = open(f, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

#include "pipex.h"

void	exit_with_error(char *str)
{
	perror(str);
	_exit(EXIT_FAILURE);
}

int	close_file_descriptor(int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == -1)
		exit_with_error("close");
	return (ret);
}

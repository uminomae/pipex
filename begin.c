#include "pipex.h"

void	check_for_valid_value(int argc)
{
	if (argc == 5)
		return ;
	else
		exit_with_error("argc");
}

void	init_struct(t_pipex *pipex,int argc, char **argv, char **env)
{
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->env = env;
}

void	create_pipe_fd(t_pipex *pipex)
{
	int ret;

	ret = pipe(pipex->pipe_fd);
	if (ret == -1)
		exit_with_error("pipe");
}

#include "pipex.h"

void	begin_pipex(t_pipex *pipex,int argc, char **argv, char **env)
{
	check_for_valid_value(argc);
	init_struct(pipex, argc, argv, env);
	create_pipe_fd(pipex);
}

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
	int status;

	status = pipe(pipex->pipe_fd);
	if (status == -1)
		exit_with_error("pipe");
}

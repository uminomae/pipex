#include "pipex.h"

void	check_for_valid_value(int argc)
{
	if (argc == 5)
		return ;
	else
	{
		perror("argc");
		exit(EXIT_FAILURE);
	}
}

void	init_struct(t_pipex *pipex,int argc, char **argv, char **env)
{
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->env = env;
	pipex->v_argv.list_absolute_path_of_command = NULL;
	pipex->v_argv.list_of_directry = NULL;
	pipex->v_argv.temp_devided_list = NULL;
	pipex->v_argv.virtual_argv = NULL;
}

//void	create_pipe_fd(t_pipex *pipex)
//{
//	int ret;

//	ret = pipe(pipex->pipe_fd);
//	if (ret == -1)
//		exit_with_error(pipex, "pipe");
//}

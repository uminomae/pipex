#include "pipex.h"

void	execute_command_read(t_pipex *pipex)
{
	char *const	*argv = (char *const *)pipex->argv;
	char		**virtual_argv;

	virtual_argv = get_virtual_argv(pipex, argv[2]);
	execve(virtual_argv[0], virtual_argv, pipex->env);
	exit(EXIT_SUCCESS);
}

void	execute_command_write(t_pipex *pipex)
{
	char *const	*argv = (char *const *)pipex->argv;
	char		**virtual_argv;

	virtual_argv = get_virtual_argv(pipex, argv[3]);
	// readでcommandが見つからない場合、"/"が入っている様子の本家挙動
	execve(virtual_argv[0], virtual_argv, pipex->env);
	exit(EXIT_SUCCESS);
}



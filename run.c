#include "pipex.h"

void	open_file(t_pipex *pipex, int in_out)
{
	char *const	*argv = (char *const *)pipex->argv;
	const int	*pipe = pipex->pipe_fd;
	int *const	file = pipex->file_fd;

	close_file_descriptor(pipe[in_out]);
	//close(pipex->pipe_fd[in_out]);
	if (in_out == READ)
		file[READ] = open(argv[1], O_RDONLY | O_CLOEXEC, 0);
		//pipex->file_fd[READ] = open(argv[1], O_RDONLY | O_CLOEXEC, 0);
	else if (in_out == WRITE)
		file[WRITE] = open(argv[4], O_WRONLY | O_CLOEXEC | \
							O_CREAT | O_TRUNC, 0777);
		//pipex->file_fd[WRITE] = open(argv[4], O_WRONLY | O_CLOEXEC | O_CREAT | O_TRUNC, 0777);
	file[READ] = -1;
	if (file[READ] == -1 | file[WRITE] == -1)
		exit_with_error("open");
}

void	execute_command_read(t_pipex *pipex)
{
	char *const	*argv = (char *const *)pipex->argv;

	//これから作るとこ。とりあえずテスト用argv1
	GET_AVG_READ;
	
	execve(argv[2], argv1_test, pipex->env);
	exit(EXIT_SUCCESS);
}

void	execute_command_write(t_pipex *pipex)
{
	char *const	*argv = (char *const *)pipex->argv;
	
	//これから作るとこ。とりあえずテスト用argv1
	GET_AVG_WRITE;

	execve(argv[3], argv1_test, pipex->env);
	exit(EXIT_SUCCESS);
}



#include "pipex.h"

void	create_child_process(t_pipex *pipex, int i)
{
	pid_t* const pid = pipex->pid;

	pid[i] = fork();
	if (pid[i] == -1)
		exit_with_error("fork");
}

void	open_file(t_pipex *pipex, int in_out)
{
	char *const	*argv = (char *const *)pipex->argv;
	const int	*pipe = pipex->pipe_fd;
	int *const	file = pipex->file_fd;

	close_file_descriptor(pipe[in_out]);
	if (in_out == READ)
		file[READ] = open(argv[1], O_RDONLY | O_CLOEXEC, 0);
	else if (in_out == WRITE)
		file[WRITE] = open(argv[4], O_WRONLY | O_CLOEXEC | \
							O_CREAT | O_TRUNC, 0777);
	//file[READ] = -1;
	if (file[READ] == -1 | file[WRITE] == -1)
		exit_with_error("open");
}

void	duplicate_to_standard_in_out(int input_source_file, int out_destination)
{
	int	ret_in;
	int	ret_out;

	ret_in = dup2(input_source_file, STANDARD_INPUT);
	close_file_descriptor(input_source_file);
	if (ret_in == -1)
		exit_with_error("dup2");
	ret_out = dup2(out_destination, STANDARD_OUTPUT);
	close_file_descriptor(out_destination);
	if (ret_out == -1)
		exit_with_error("dup2");
}

void	wait_for_child_process(t_pipex *pipex, int i)
{
	pid_t	ret_pid;
	int		child_status;

	ret_pid = waitpid(pipex->pid[i], &child_status, 0);
	//ret_pid = waitpid(pipex->pid[i], &pipex->child_status[i], 0);
	if (ret_pid == -1)
		exit_with_error("waitpid");
}
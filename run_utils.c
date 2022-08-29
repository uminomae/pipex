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

void	create_child_process(t_pipex *pipex, int i)
{
	pid_t* const pid = pipex->pid;

	pid[i] = fork();
	if (pid[i] == -1)
		exit_with_error("fork");
}

//statusが分かりづらい。なんの？
void	wait_for_child_process(t_pipex *pipex, int i)
{
	pid_t	ret_pid;

	ret_pid = waitpid(pipex->pid[i], &pipex->status[i], 0);
	if (ret_pid == -1)
		exit_with_error("waitpid");
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
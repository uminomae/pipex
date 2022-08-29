#include "pipex.h"

void	exit_with_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	create_child_process(t_pipex *pipex, int i)
{
	pid_t* const pid = pipex->pid;

	pid[i] = fork();
	if (pid[i] == -1)
		exit_with_error("fork");
}

void	wait_for_child_process(t_pipex *pipex, int i)
{
	pid_t	ret;

	ret = waitpid(pipex->pid[i], &pipex->status[i], 0);
	if (ret == -1)
		exit_with_error("waitpid");
}

void	switch_to_standard_in_out(int old_in_fd, int old_out_fd)
{
	int	ret_in;
	int	ret_out;

	ret_in = dup2(old_in_fd, READ);
	close(old_in_fd);
	if (ret_in == -1)
		exit_with_error("dup2");
	ret_out = dup2(old_out_fd, WRITE);
	close(old_out_fd);
	if (ret_out == -1)
		exit_with_error("dup2");
}
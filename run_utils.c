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

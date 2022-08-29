#include "pipex.h"

void	run_read_side(t_pipex *pipex, int i)
{
	create_child_process(pipex, i);
	if (pipex->pid[i] == 0)
		run_read_side_child_process(pipex);
	wait_for_child_process(pipex, i);
}

void	run_write_side(t_pipex *pipex, int i)
{
	create_child_process(pipex, i);
	if (pipex->pid[i] == 0)
		run_write_side_child_process(pipex);
	close(pipex->pipe_fd[i]);
	close(pipex->pipe_fd[READ]);
	wait_for_child_process(pipex, i);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex pipex;

	begin_pipex(&pipex, argc, argv, env);
	run_read_side(&pipex, READ);
	//wait_for_child_process(&pipex, READ);
	run_write_side(&pipex, WRITE);
	//wait_for_child_process(&pipex, WRITE);
	return (0);
}

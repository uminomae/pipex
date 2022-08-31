#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex pipex;

	begin_pipex(&pipex, argc, argv, env);
	create_pipe_fd(&pipex);
	run_read_side(&pipex, READ);
	//wait_for_child_process(&pipex, READ);
	run_write_side(&pipex, WRITE);
	//close_unused_file_descriptor(pipex.pipe_fd[WRITE]);
	//close_unused_file_descriptor(pipex.pipe_fd[READ]);
	//wait_for_child_process(&pipex, WRITE);

	return (0);
}
	//system("leaks -q pipex");

void	begin_pipex(t_pipex *pipex,int argc, char **argv, char **env)
{
	check_for_valid_value(argc);
	init_struct(pipex, argc, argv, env);
}

void	run_read_side(t_pipex *pipex, int i)
{
	const int	*pipe = pipex->pipe_fd;
	int *const	file = pipex->file_fd;

	create_child_process(pipex, i);
	if (pipex->pid[i] == 0)
	{
		close_unused_file_descriptor(pipex, pipe[i]);
		open_file(pipex, i);
		duplicate_to_standard_in_out(pipex, file[READ], pipe[WRITE]);
		execute_command_read(pipex);
		close_unused_file_descriptor(pipex, file[i]);
	}
	wait_for_child_process(pipex, i);
}

void	run_write_side(t_pipex *pipex, int i)
{
	const int	*pipe = pipex->pipe_fd;
	int *const	file = pipex->file_fd;

	create_child_process(pipex, i);
	if (pipex->pid[i] == 0)
	{
		close_unused_file_descriptor(pipex, pipe[i]);
		open_file(pipex, i);
		duplicate_to_standard_in_out(pipex, pipe[READ], file[WRITE]);
		execute_command_write(pipex);
		close_unused_file_descriptor(pipex, file[i]);
	}
	close_both_pipe(pipex);
	wait_for_child_process(pipex, i);
}

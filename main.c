#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex pipex;

	begin_pipex(&pipex, argc, argv, env);
	run_read_side(&pipex, READ);
	//wait_for_child_process(&pipex, READ);
	run_write_side(&pipex, WRITE);
	//close(pipex.pipe_fd[WRITE]);
	//close(pipex.pipe_fd[READ]);
	//wait_for_child_process(&pipex, WRITE);
	return (0);
}

void	begin_pipex(t_pipex *pipex,int argc, char **argv, char **env)
{
	check_for_valid_value(argc);
	init_struct(pipex, argc, argv, env);
	create_pipe_fd(pipex);
}

void	run_read_side(t_pipex *pipex, int i)
{
	const int	*pipe = pipex->pipe_fd;
	const int	*file = pipex->file_fd;

	create_child_process(pipex, i);
	if (pipex->pid[i] == 0)
	{
		open_file(pipex, i);
		duplicate_to_standard_in_out(file[READ], pipe[WRITE]);
		execute_command_read(pipex);
	}
	wait_for_child_process(pipex, i);
}

void	run_write_side(t_pipex *pipex, int i)
{
	const int	*pipe = pipex->pipe_fd;
	const int	*file = pipex->file_fd;

	create_child_process(pipex, i);
	if (pipex->pid[i] == 0)
	{
		open_file(pipex, i);
		duplicate_to_standard_in_out(pipe[READ], file[WRITE]);
		execute_command_write(pipex);
	}
	close(pipex->pipe_fd[WRITE]);
	close(pipex->pipe_fd[READ]);
	wait_for_child_process(pipex, i);
}

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex pipex;

	begin_pipex(&pipex, argc, argv, env);
	run_read_side(&pipex, READ);
	//wait_for_child_process(&pipex, READ);
	run_write_side(&pipex, WRITE);
	//close_file_descriptor(pipex.pipe_fd[WRITE]);
	//close_file_descriptor(pipex.pipe_fd[READ]);
	//wait_for_child_process(&pipex, WRITE);

	//system("leaks -q pipex");
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
	int *const	file = pipex->file_fd;

	create_child_process(pipex, i);
	if (pipex->pid[i] == 0)
	{
		close_file_descriptor(pipex, pipe[i]);
		open_file(pipex, i);

		//char **virtual_argv = 
		//get_virtual_argv(pipex, pipex->argv[2]);
		//printf("%s", virtual_argv[0]);

		duplicate_to_standard_in_out(pipex, file[READ], pipe[WRITE]);
		execute_command_read(pipex);
		close_file_descriptor(pipex, file[i]);
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
		close_file_descriptor(pipex, pipe[i]);
		open_file(pipex, i);
		duplicate_to_standard_in_out(pipex, pipe[READ], file[WRITE]);
		execute_command_write(pipex);
		close_file_descriptor(pipex, file[i]);
	}
	close_file_descriptor(pipex, pipe[WRITE]);
	close_file_descriptor(pipex, pipe[READ]);
	wait_for_child_process(pipex, i);
}

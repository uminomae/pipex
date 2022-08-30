#include "pipex.h"

int		test_env(t_pipex *pipex);


int	test_env(t_pipex *pipex)
{
	size_t	i;
	char	**list_dir;

	i = get_path_line_from_env(pipex);
	list_dir = get_list_of_directry_from_path_line(pipex, i);

	// test split
	//
	size_t	j;
	for (j=0; list_dir[j] != NULL; j++)
		printf("%s\n", list_dir[j]);
	//
	//

	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex pipex;

	begin_pipex(&pipex, argc, argv, env);
	test_env(&pipex);

	run_read_side(&pipex, READ);
	//wait_for_child_process(&pipex, READ);
	run_write_side(&pipex, WRITE);
	//close_file_descriptor(pipex.pipe_fd[WRITE]);
	//close_file_descriptor(pipex.pipe_fd[READ]);
	//wait_for_child_process(&pipex, WRITE);
	return (0);
}

void	begin_pipex(t_pipex *pipex,int argc, char **argv, char **env)
{
	//check_for_valid_value(argc);
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
		close_file_descriptor(pipe[i]);
		open_file(pipex, i);
		duplicate_to_standard_in_out(file[READ], pipe[WRITE]);
		execute_command_read(pipex);
		close_file_descriptor(file[i]);
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
		close_file_descriptor(pipe[i]);
		open_file(pipex, i);
		duplicate_to_standard_in_out(pipe[READ], file[WRITE]);
		execute_command_write(pipex);
		close_file_descriptor(file[i]);
	}
	close_file_descriptor(pipe[WRITE]);
	close_file_descriptor(pipe[READ]);
	wait_for_child_process(pipex, i);
}

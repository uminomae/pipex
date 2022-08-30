#include "pipex.h"

//void	test_print()
//{
//	// test split
//	size_t	j;
//	for (j=0; list_of_directry[j] != NULL; j++)
//		printf("%s\n", list_of_directry[j]);
//	//

//	// test strrchr
//	printf("%s\n", command_name);
//	printf("%s\n", get_absolute_path);
//	//
//}

int	main(int argc, char **argv, char **env)
{
	t_pipex pipex;

	begin_pipex(&pipex, argc, argv, env);
	
	// test
	get_absolute_path(&pipex, argv[2]);
	//

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
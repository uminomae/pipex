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

void	begin_pipex(t_pipex *pipex,int argc, char **argv, char **env)
{
	check_for_valid_value(argc);
	init_struct(pipex, argc, argv, env);
	create_pipe_fd(pipex);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex pipex;

	begin_pipex(&pipex, argc, argv, env);

	create_child_process(&pipex, READ);
	if (pipex.pid[READ] == 0)
		run_read_side_child_process(&pipex);
	wait_for_child_process(&pipex, READ);
	//printf("main()-----\n");
	create_child_process(&pipex, WRITE);
	if (pipex.pid[WRITE] == 0)
		run_write_side_child_process(&pipex);
	close(pipex.pipe_fd[WRITE]);
	wait_for_child_process(&pipex, WRITE);
	close(pipex.pipe_fd[READ]);
	return (0);
}

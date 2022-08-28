#include "pipex.h"

void	child_process(char **argv, char **env, int *pipe_fd)
{
	int read_fd;

	read_fd = open(argv[1], O_RDONLY, 0);
	dup2(pipe_fd[WRITE], STANDARD_OUTPUT);
	dup2(read_fd, STANDARD_INPUT);
	close(pipe_fd[READ]);
	//execute(argv[2], env);
	//exec_child(argv[2], env, read_fd, pipe_fd[WRITE]);
	(void)env;
}

void	parent_process(char **argv, char **env, int *pipe_fd)
{
	int write_fd;

	write_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(pipe_fd[READ],STANDARD_INPUT);
	dup2(write_fd, STANDARD_OUTPUT);
	close(pipe_fd[WRITE]);
	//execute(argv[3], env);
	//exec_child(argv[3],env, pipe_fd[READ], write_fd);
	(void)env;
}

//void run_pipe(char **argv, char **env, t_pipex *pipex)
//{
//	if (pipex->pid == 0)
//		child_process(argv, env, pipex->pipe_fd);
//	waitpid(pipex->pid, NULL, 0);
//	parent_process(argv, env, pipex->pipe_fd);
//}

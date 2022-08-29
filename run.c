#include "pipex.h"

void	run_read_side_child_process(t_pipex *pipex)
{
	char *const	*argv = (char *const *)pipex->argv;
	const int	*pipe = pipex->pipe_fd;

	close(pipe[READ]);
	pipex->file_fd[READ] = open(argv[1], O_RDONLY, 0);
	switch_to_standard_in_out(pipex->file_fd[READ], pipe[WRITE]);

	//これから作るとこ。とりあえずテスト用argv1
	GET_AVG_READ;
	
	execve(argv[2], argv1_test, pipex->env);
	exit(EXIT_SUCCESS);
}

void	run_write_side_child_process(t_pipex *pipex)
{
	const int	*pipe = pipex->pipe_fd;
	char *const	*argv = (char *const *)pipex->argv;

	close(pipe[WRITE]);
	//OPEN関数を調べる
	pipex->file_fd[WRITE] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	switch_to_standard_in_out(pipe[READ], pipex->file_fd[WRITE]);
	
	//これから作るとこ。とりあえずテスト用argv1
	GET_AVG_WRITE;

	execve(argv[3], argv1_test, pipex->env);
	exit(EXIT_SUCCESS);
}



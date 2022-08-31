#include "pipex.h"

void	create_child_process_by_fork_func(t_pipex *pipex, int i)
{
	pid_t* const pid = pipex->pid;

	pid[i] = fork();
	// TODO err check OK
	//pid[i] = -1;
	if (pid[i] == -1)
	{
		close_both_pipe(pipex);
		exit_with_error_child_process(pipex, "fork");
	}
}

//file[WRITE] is likea a chmod 644
void	open_file(t_pipex *pipex, int in_out)
{
	char *const	*argv = (char *const *)pipex->argv;
	int *const	file = pipex->file_fd;

	if (in_out == READ)
		file[READ] = open(argv[1], O_RDONLY | O_CLOEXEC, 0);
	else if (in_out == WRITE)
		file[WRITE] = \
			open(argv[4], O_WRONLY | O_CLOEXEC | O_CREAT | O_TRUNC, \
							S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	// TODO err check OK leaks 単独ならエラー出ない
	//file[READ] = -1;
	// TODO err check OK leaks 単独ならエラー出ない
	//file[WRITE] = -1;
	if (file[READ] == -1 | file[WRITE] == -1)
		exit_with_error_child_process(pipex, "open");
}

void	duplicate_to_standard_in_out(t_pipex *pipex, int file_for_reading, int file_for_writing)
{
	int	ret_in;
	int	ret_out;

	ret_in = dup2(file_for_reading, STANDARD_INPUT);
	close_unused_file_descriptor(pipex, file_for_reading);
	// TODO err check OK leaks 単独ならエラー出ない
	//ret_in = -1;
	if (ret_in == -1)
		exit_with_error_child_process(pipex, "dup2");
	ret_out = dup2(file_for_writing, STANDARD_OUTPUT);
	close_unused_file_descriptor(pipex, file_for_writing);
	// TODO err check OK leaks 単独ならエラー出ない
	//ret_out = -1;
	if (ret_out == -1)
		exit_with_error_child_process(pipex, "dup2");
}

//第３引数 == 0
//プロセスグループ ID が、waitpid() が呼ばれた時点での
//呼び出し元のプロセスのプロセスグループ ID と等しい子プロセスを待つ。
void	wait_pid_for_child_process(t_pipex *pipex, int i)
{
	pid_t	ret_pid;
	int		child_status;

	ret_pid = waitpid(pipex->pid[i], &child_status, 0);
	// TODO err check OK
	//ret_pid = -1;
	if (ret_pid == -1)
		exit_with_error_child_process(pipex, "waitpid");
}
#include "pipex.h"

void	run_read_side_child_process(t_pipex *pipex)
{
	char *const	*argv = (char *const *)pipex->argv;
	const int	*pipe = pipex->pipe_fd;
	int			read_file;

	//使わない
	close(pipe[READ]);

	read_file = open(argv[1], O_RDONLY, 0);
	dup2(read_file, 0);
	close(read_file);

	//pipeの書き込み側をfd=1番にする。使わないfdは閉じる
	dup2(pipe[WRITE], 1);
	close(pipe[WRITE]);

	char *argv1_test[3];
	argv1_test[0] = "/usr/bin/grep";
	argv1_test[1] = "a1";
	argv1_test[2] = NULL;
	execve(argv[2], argv1_test, pipex->env);

	close(0);
	close(1);
	exit(EXIT_SUCCESS);
}

void	run_write_side_child_process(t_pipex *pipex)
{
	const int	*pipe = pipex->pipe_fd;

	close(pipe[WRITE]);

	//file読み込み用。本家の動きが課題と違う。。
	char *const	*argv = (char *const *)pipex->argv;
	int 		write_file;
	write_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(write_file, 1);
	close(write_file);

	//pipeの読み込み側をfd=0番にする
	//close(pipe[WRITE]);
	dup2(pipe[READ], 0);
	close(pipe[READ]);

	//とりあえずpipe_fdの動きを確認用printf
	//char		buf[256];
	//read(0, buf, sizeof buf);
	//printf("%s", buf);

	char *argv1_test[3];
	argv1_test[0] = "/bin/cat";
	argv1_test[1] = NULL;
	argv1_test[2] = NULL;
	//commandを実行する
	execve(argv[3], argv1_test, pipex->env);

	close(0);
	close(1);
	exit(EXIT_SUCCESS);
}



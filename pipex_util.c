#include "pipex.h"

void	exit_with_error(char *str)
{
	perror(str);
	_exit(EXIT_FAILURE);
}

//pipeを閉じているのか、fileを閉じているのか共通化すると分かりづらい
int	close_file_descriptor(int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == -1)
		exit_with_error("close");
	return (ret);
}

// pipe()後 && 子プロセスのifの前段階で使用。今のとこfork()失敗時のみ。
//
// エラーによるexit時のpipeのcloseは、fork()までのエラー
// 子プロセスは親の分が残ってるのでスルー、親プロセス終了時に行う。
// ※子プロセス内では使わない方を閉じる。
// open()したfdのcloseは、O_CLOEXECオプションで対応できる？
// ※子プロセス内でopen()したfdは子プロセスの最後でclose
// エラー時どうする？
void	close_pipe_and_exit(t_pipex *pipex, char *str)
{
	close_file_descriptor(pipex->pipe_fd[WRITE]);
	close_file_descriptor(pipex->pipe_fd[READ]);
	perror(str);
	_exit(EXIT_FAILURE);
}
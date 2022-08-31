#include "pipex.h"

int	close_unused_file_descriptor(t_pipex *pipex, int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == -1)
		exit_with_error_child_process(pipex, "close");
	return (ret);
}

// エラーによるexit時のpipeのcloseは、fork()までのエラー
// 子プロセスは親の分が残ってるのでスルー、親プロセス終了時に行う。
// ※子プロセス内でopen()したfdは子プロセスの最後でclose
// エラー時どうする？
void	close_both_pipe(t_pipex *pipex)
{
	close_unused_file_descriptor(pipex, pipex->pipe_fd[READ]);
	close_unused_file_descriptor(pipex, pipex->pipe_fd[WRITE]);
}

#include "pipex.h"

//exitとまとめてfreeとclosepipeを分ける。
void	exit_with_error(t_pipex *pipex, char *str)
{
	(void)pipex;
	//free_list_absolute_path_of_command(&pipex->v_argv);
	//free_virtual_argv(&pipex->v_argv);
	//free_list_of_directry(&pipex->v_argv);
	//free_temp_devided_list(&pipex->v_argv);
	perror(str);
	_exit(EXIT_FAILURE);
}

//pipeを閉じているのか、fileを閉じているのか共通化すると分かりづらい
int	close_file_descriptor(t_pipex *pipex, int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == -1)
		exit_with_error(pipex, "close");
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
void	close_pipe_and_exit_with_error(t_pipex *pipex, char *str)
{
	close_file_descriptor(pipex, pipex->pipe_fd[WRITE]);
	close_file_descriptor(pipex, pipex->pipe_fd[READ]);
	perror(str);
	_exit(EXIT_FAILURE);
}

void	safe_free(char **malloc_ptr)
{
	free(*malloc_ptr);
	*malloc_ptr = NULL;
}

size_t	count_ptr(char **list)
{
	size_t i;

	i = 0;
	while (list[i] != NULL)
	{
		i++;
	}
	i++;
	return (i);
}
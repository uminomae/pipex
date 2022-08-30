#include "pipex.h"

void	execute_command_read(t_pipex *pipex)
{
	char *const	*argv = (char *const *)pipex->argv;
	char		*path_name;

	path_name = get_absolute_path(pipex, argv[2]);

	//これから作るとこ。とりあえずテスト用argv1
	GET_AVG_READ;

	execve(path_name, argv1_test, pipex->env);
	exit(EXIT_SUCCESS);
}

void	execute_command_write(t_pipex *pipex)
{
	char *const	*argv = (char *const *)pipex->argv;
	char		*path_name;

	path_name = get_absolute_path(pipex, argv[3]);

	// readでcommandが見つからない場合、"/"が入っている様子の本家挙動
	//これから作るとこ。とりあえずテスト用argv1
	GET_AVG_WRITE;

	execve(path_name, argv1_test, pipex->env);
	exit(EXIT_SUCCESS);
}



#include "pipex.h"

void	execute_command_read(t_pipex *pipex)
{
	char *const	*argv = (char *const *)pipex->argv;

	//これから作るとこ。とりあえずテスト用argv1
	GET_AVG_READ;
	
	execve(argv[2], argv1_test, pipex->env);
	exit(EXIT_SUCCESS);
}

void	execute_command_write(t_pipex *pipex)
{
	char *const	*argv = (char *const *)pipex->argv;
	
	//これから作るとこ。とりあえずテスト用argv1
	GET_AVG_WRITE;

	execve(argv[3], argv1_test, pipex->env);
	exit(EXIT_SUCCESS);
}



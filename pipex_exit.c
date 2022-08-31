#include "pipex.h"

//exitとまとめてfreeとclosepipeを分ける。
void	exit_with_error(t_pipex *pipex, char *str)
{
	(void)pipex;
	free_list_absolute_path_of_command(&pipex->v_argv);
	free_virtual_argv(&pipex->v_argv);
	free_list_of_directry(&pipex->v_argv);
	free_temp_devided_list(&pipex->v_argv);
	perror(str);
	_exit(EXIT_FAILURE);
}

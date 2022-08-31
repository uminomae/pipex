#include "pipex.h"

void	execute_command(t_pipex *pipex, char *argv)
{
	//char *const	*argv = (char *const *)pipex->argv;
	char		**virtual_argv;

	virtual_argv = get_virtual_argv(pipex, argv);
	execve(virtual_argv[0], virtual_argv, pipex->env);
	_exit(EXIT_SUCCESS);
}

//void	execute_command_read(t_pipex *pipex)
//{
//	char *const	*argv = (char *const *)pipex->argv;
//	char		**virtual_argv;

//	virtual_argv = get_virtual_argv(pipex, argv[2]);
//	execve(virtual_argv[0], virtual_argv, pipex->env);
//	_exit(EXIT_SUCCESS);
//}

////共通化する
//void	execute_command_write(t_pipex *pipex)
//{
//	char *const	*argv = (char *const *)pipex->argv;
//	char		**virtual_argv;

//	virtual_argv = get_virtual_argv(pipex, argv[3]);
//	// readでcommandが見つからない場合、"/"が入っている様子の本家挙動
//	execve(virtual_argv[0], virtual_argv, pipex->env);
//	_exit(EXIT_SUCCESS);
//}

char	**get_virtual_argv(t_pipex *pipex, char *command_from_argv)
{
	size_t		path_line;
	size_t		index;
	t_v_argv	*v;
	
	v = &pipex->v_argv;
	path_line = get_path_line_from_env(pipex);
	v->temp_devided_list = split_list_of_directry_from_path_line(pipex, path_line);
	v->list_of_directry = join_slash_path_of_directory(v->temp_devided_list);
	v->virtual_argv = split_virtual_argv_from_real_argv(pipex, command_from_argv);
	v->list_absolute_path_of_command = join_basename_absolute_path(v->list_of_directry, v->virtual_argv[0]);
	index = get_index_accessible_path(pipex, v->list_absolute_path_of_command);
	v->virtual_argv = switch_first_argv_to_absolute_path(v, index);
	return (v->virtual_argv);
}

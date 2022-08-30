#include "pipex.h"

char	**get_absolute_path(t_pipex *pipex, char *command_from_argv)
{
	size_t	path_line;
	char	**list_of_directry;
	char	**virtual_argv;
	char	*absolute_path;

	path_line = get_path_line_from_env(pipex);
	list_of_directry = get_list_of_directry_from_path_line(pipex, path_line);
	//malloc split
	virtual_argv = get_virtual_argv_from_real_argv(command_from_argv);
	absolute_path = make_absolute_path(list_of_directry, virtual_argv[0]);
	//malloc strjoin
	virtual_argv[0] = absolute_path;
	return (virtual_argv);
}

size_t	get_path_line_from_env(t_pipex *pipex)
{
	size_t i;
	
	i = 0;
	while(pipex->env[i] != NULL)
	{
		if (ft_strncmp(pipex->env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (0);
}

char	**get_list_of_directry_from_path_line(t_pipex *pipex, size_t path_index)
{
	size_t	trim_len;
	char	**list;
	
	list = NULL;
	list = ft_split(pipex->env[path_index], ':');
	//malloc失敗時
	trim_len = ft_strlen("PATH=");
	list[0] = list[0] + trim_len;
	return (list);
}

char	**get_virtual_argv_from_real_argv(char *command_from_argv)
{
	char **virtual_argv;
	char *name_and_option;

	if (command_from_argv == NULL)
	//free()
		exit_with_error("argv");
	virtual_argv = NULL;
	name_and_option = NULL;
	name_and_option = ft_strrchr(command_from_argv, '/');
	if (name_and_option == NULL)
		name_and_option = command_from_argv;
	virtual_argv = ft_split(name_and_option, ' ');
	return (virtual_argv);
}

char	*make_absolute_path(char **list_of_directry, char *command_name)
{
	size_t	i;
	char	*path_name;

	i = 0;
	while (list_of_directry[i] != NULL)
	{
		path_name = ft_strjoin(list_of_directry[i], command_name);
		//malloc失敗時、splitも
		if (access(path_name, R_OK) == 0)
			return (path_name);
		i++;
	}
	// command not foundにする方法は？
	exit_with_error("access");
	return (NULL);
}



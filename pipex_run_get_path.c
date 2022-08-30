#include "pipex.h"

char	*get_absolute_path(t_pipex *pipex, char *command_from_argv)
{
	size_t	i;
	char	**list_of_directry;
	char	*command_name;
	char	*get_absolute_path;

	i = get_path_line_from_env(pipex);
	list_of_directry = get_list_of_directry_from_path_line(pipex, i);
	//malloc split
	command_name = get_command_name_from_argv(command_from_argv);
	get_absolute_path = make_absolute_path(list_of_directry, command_name);
	//malloc strjoin
	return (get_absolute_path);
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
	trim_len =ft_strlen("PATH=");
	list[0] = list[0] + trim_len;
	return (list);
}

char	*get_command_name_from_argv(char *command_from_argv)
{
	char *basename;

	if (command_from_argv == NULL)
	//free()
		exit_with_error("argv");
	basename = NULL;
	basename = ft_strrchr(command_from_argv, '/');
	if (basename == NULL)
		basename = command_from_argv;
	return (basename);
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



#include "pipex.h"

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
	trim_len =ft_strlen("PATH=");
	list[0] = list[0] + trim_len;
	return (list);
}

char	*get_command_name_from_argv(t_pipex *pipex)
{
	char *basename;

	if (pipex->argv[2] == NULL)
	//free()
		exit_with_error("argv");
	basename = NULL;
	basename = ft_strrchr(pipex->argv[2], '/');
	if (basename == NULL)
		basename = pipex->argv[2];
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
		if (access(path_name, R_OK) == 0)
			return (path_name);
		i++;
	}
	exit_with_error("arccess");
	return (NULL);
}

void	execute_command_read(t_pipex *pipex)
{
	char *const	*argv = (char *const *)pipex->argv;

	//char	*path_name;

	//if (access(path_name ,R_OK) = -1)
	//	exit_with_error("arccess");
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



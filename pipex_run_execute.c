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
	char	**list_of_directry;
	
	list_of_directry = NULL;
	list_of_directry = ft_split(pipex->env[path_index], ':');
	trim_len =ft_strlen("PATH=");
	list_of_directry[0] = list_of_directry[0] + trim_len;
	return (list_of_directry);
}


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



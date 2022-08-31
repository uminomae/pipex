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

char	**split_list_of_directry_from_path_line(t_pipex *pipex, size_t path_index)
{
	size_t	trim_len;
	char	**list;
	
	list = NULL;
	list = ft_split(pipex->env[path_index], ':');
	//malloc失敗時
	trim_len = ft_strlen("PATH=");
	//void *tmp;
	//tmp = list[0];
	//freeできない書き方してる
	list[0] = ft_substr(list[0] + trim_len, 0 ,ft_strlen(list[0]));
	//free(tmp);
	return (list);
}

char	**join_slash_path_of_directory(char **temp_devided_list)
{
	char	**list_of_directry;
	size_t	i;
	size_t	len;

	list_of_directry = NULL;
	len = count_pointer_including_null(temp_devided_list);
	list_of_directry = malloc(sizeof(char *) * len);
	i = 0;
	while (temp_devided_list[i] != NULL)
	{
		list_of_directry[i] = ft_strjoin(temp_devided_list[i], "/");
		//safe_free(&temp_devided_list[i]);
		i++;
	}
	list_of_directry[i] = NULL;
	//safe_free(&temp_devided_list[i]);
	//free(temp_devided_list);
	//temp_devided_list = NULL;
	return (list_of_directry);
}

char	**split_virtual_argv_from_real_argv(t_pipex *pipex, char *command_from_argv)
{
	char **virtual_argv;

	if (command_from_argv == NULL)
	//free()
		exit_with_error(pipex, "argv");
	virtual_argv = ft_split(command_from_argv, ' ');
	return (virtual_argv);
}

char	**join_basename_absolute_path(char **list_of_directry, char *command_name)
{
	char	**list_absolute_path_of_command;
	size_t	i;
	size_t	len;

	list_absolute_path_of_command = NULL;
	len = count_pointer_including_null(list_of_directry);
	list_absolute_path_of_command = malloc(sizeof(char *) * len);
	i = 0;
	while (list_of_directry[i] != NULL)
	{
		list_absolute_path_of_command[i] = ft_strjoin(list_of_directry[i], command_name);
		//safe_free(&list_of_directry[i]);
		//malloc失敗時、splitも
		i++;
	}
	list_absolute_path_of_command[i] = NULL;
	//safe_free(&list_of_directry[i]);
	//free(list_of_directry);
	//list_of_directry = NULL;
	return (list_absolute_path_of_command);
}

size_t	get_index_accessible_path(t_pipex *pipex, char **list_absolute_path_of_command)
{
	size_t	i;
	i=0;
	while (list_absolute_path_of_command[i] != NULL)
	{
		if (access(list_absolute_path_of_command[i], R_OK) == 0)
			return (i);
		i++;
	}
// command not foundにする方法は？
	exit_with_error(pipex, "access");
	return (-1);
}

char	**switch_first_argv_to_absolute_path(t_v_argv *v, size_t index)
{
	void		*tmp;
	tmp = v->virtual_argv[0];
	v->virtual_argv[0] = ft_strdup(v->list_absolute_path_of_command[index]);
	free(tmp);
	return (v->virtual_argv);
}
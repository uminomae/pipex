#include "pipex.h"

size_t	get_accessible_path(char **list_absolute_path)
{
	size_t	i;
	i=0;
	while (list_absolute_path[i] != NULL)
	{
		if (access(list_absolute_path[i], R_OK) == 0)
			return (i);
		i++;
	}

	exit_with_error("access");
	return (-1);
}

char	**get_virtual_argv(t_pipex *pipex, char *command_from_argv)
{
	size_t	path_line;
	char	**list_of_directry;
	char	**list_of_directry_full;
	char	**virtual_argv;

	path_line = get_path_line_from_env(pipex);
	list_of_directry = get_list_of_directry_from_path_line(pipex, path_line);
	printf("c---%s\n", list_of_directry[0]);

	list_of_directry_full = add_slash(list_of_directry);
	printf("b---%s\n", list_of_directry_full[0]);
	virtual_argv = make_virtual_argv_from_real_argv(command_from_argv);
	printf("a---%s\n", virtual_argv[0]);

	char	**list_absolute_path;
	list_absolute_path = make_absolute_path(list_of_directry_full, virtual_argv[0]);
	printf("e---%s\n", list_absolute_path[0]);
	//malloc strjoin
	//malloc strjoin
	//malloc split

	size_t	i;
	i = get_accessible_path(list_absolute_path);
	void *tmp;
	tmp = virtual_argv[0];
	virtual_argv[0] = ft_strdup(list_absolute_path[i]);
	free(tmp);
	printf("f---%s\n", virtual_argv[0]);
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
	void *tmp;
	tmp = list[0];
	//list[0] = list[0] + trim_len;
	//freeできない書き方してる
	list[0] = ft_substr(list[0] + trim_len, 0 ,ft_strlen(list[0]));
	free(tmp);
	return (list);
}

char	**add_slash(char **list_of_directry)
{
	char	**list_of_directry_full;
	size_t	i;
	size_t	len;

	list_of_directry_full = NULL;
	len = ft_strlen(*list_of_directry);
	list_of_directry_full = malloc(sizeof(char *) * len);
	i = 0;
	while (list_of_directry[i] != NULL)
	{
		list_of_directry_full[i] = ft_strjoin(list_of_directry[i], "/");
		safe_free(&list_of_directry[i]);
		//free(list_of_directry[i]);
		i++;
	}
	safe_free(&list_of_directry[i]);
	free(list_of_directry);
	list_of_directry = NULL;
	return (list_of_directry_full);
}

char	**make_virtual_argv_from_real_argv(char *command_from_argv)
{
	char **virtual_argv;
	//char *name_and_option;

	if (command_from_argv == NULL)
	//free()
		exit_with_error("argv");
	virtual_argv = NULL;
	//name_and_option = NULL;
	//name_and_option = ft_strrchr(command_from_argv, '/');
	//if (name_and_option == NULL)
	//	name_and_option = command_from_argv;
	virtual_argv = ft_split(command_from_argv, ' ');
	//virtual_argv = ft_split(name_and_option, ' ');
	//printf("a-----%s\n", virtual_argv[0]);
	return (virtual_argv);
}

char	**make_absolute_path(char **list_of_directry_full, char *command_name)
{
	char	**list_absolute_path;
	size_t	i;
	size_t	len;

	list_absolute_path = NULL;
	len = ft_strlen(*list_of_directry_full);
	list_absolute_path = malloc(sizeof(char *) * len);
	i = 0;
	while (list_of_directry_full[i] != NULL)
	{
		list_absolute_path[i] = ft_strjoin(list_of_directry_full[i], command_name);
		//safe_free(&list_of_directry_full[i]);
		//malloc失敗時、splitも
		//if (access(list_absolute_path[i], R_OK) == 0)
		//{
		//	//list_absolute_path = list_absolute_path[i];
		//	return (list_absolute_path[i]);
		//}
		//free(list_absolute_path[i]);
		i++;
	}
	//safe_free(&list_of_directry_full[i]);
	//free(list_of_directry_full);
	// command not foundにする方法は？

	//exit_with_error("access");
	return (list_absolute_path);
}



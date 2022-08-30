#include "pipex.h"

void	safe_free(char *malloc_pp)
{
	free(malloc_pp);
	malloc_pp = NULL;
}

void	test_print_duble(char **list)
{
	size_t i =0;
	while (list[i] != NULL)
	{
		printf("%s", list[i]);
		i++;
	}
}
char	**add_slash(char **list_of_directry)
{
	char	**cpy;
	size_t	i;

	cpy = NULL;

	size_t len;
	len = ft_strlen(*list_of_directry);
	printf("d------%zu\n",len);

	cpy = malloc(sizeof(char *) * len);

	i = 0;
	while (list_of_directry[i] != NULL)
	{
		cpy[i] = ft_strjoin(list_of_directry[i], "/");
		printf("add / -----%s\n", cpy[i]);
		//safe_free(list_of_directry[i]);
		i++;
	}
	//free(list_of_directry);

	//test_print_duble(cpy);

	return (cpy);
}

char	**get_virtual_argv(t_pipex *pipex, char *command_from_argv)
{
	size_t	path_line;
	char	**list_of_directry;
	char	**list_of_directry_full;
	char	**virtual_argv;
	char	*absolute_path;

	path_line = get_path_line_from_env(pipex);
	list_of_directry = get_list_of_directry_from_path_line(pipex, path_line);
	list_of_directry_full = add_slash(list_of_directry);
	virtual_argv = make_virtual_argv_from_real_argv(command_from_argv);
	//malloc split
	absolute_path = make_absolute_path(list_of_directry_full, virtual_argv[0]);
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

char	*make_absolute_path(char **list_of_directry, char *command_name)
{
	size_t	i;
	char	*absolute_path;
	//char	*tmp;

	i = 0;
	while (list_of_directry[i] != NULL)
	{
		//tmp = list_of_directry[i];
		//list_of_directry[i] = ft_strjoin(list_of_directry[i], "/");
		//free(tmp);
		absolute_path = ft_strjoin(list_of_directry[i], command_name);
		//malloc失敗時、splitも
		if (access(absolute_path, R_OK) == 0)
			return (absolute_path);
		i++;
	}
	// command not foundにする方法は？

	exit_with_error("access");
	return (NULL);
}



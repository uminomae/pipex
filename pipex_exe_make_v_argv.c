#include "pipex.h"

char	**split_virtual_argv_from_real_argv(t_pipex *pipex, char *command_from_argv)
{
	char **virtual_argv;

	// TODO err check OK
	//command_from_argv = NULL;
	if (command_from_argv == NULL)
		exit_with_error(pipex, "argv");
	virtual_argv = ft_split(command_from_argv, ' ');
	// TODO err check OK
	//virtual_argv = NULL;
	if (virtual_argv == NULL)
		exit_with_error(pipex, "ft_split");
	return (virtual_argv);
}

char	**join_file_and_directry_name_to_get_absolute_path(t_pipex *pipex, char **list_of_directry, char *command_name)
{
	char	**list_absolute_path_of_command;
	size_t	i;
	size_t	num;

	list_absolute_path_of_command = NULL;
	num = count_pointer_including_null(list_of_directry);
	list_absolute_path_of_command = malloc(sizeof(char *) * num);
	i = 0;
	while (list_of_directry[i] != NULL)
	{
		list_absolute_path_of_command[i] = ft_strjoin(list_of_directry[i], command_name);
		safe_free(&list_of_directry[i]);
		// TODO err check OK
		//list_absolute_path_of_command = NULL;
		if (list_absolute_path_of_command == NULL)
			exit_with_error(pipex, "ft_strjoin");
		i++;
	}
	list_absolute_path_of_command[i] = NULL;
	safe_free(&list_of_directry[i]);
	free(list_of_directry);
	list_of_directry = NULL;
	return (list_absolute_path_of_command);
}

size_t	get_index_accessible_path(t_pipex *pipex, char **list_absolute_path_of_command)
{
	size_t	i;

	i = 0;
	// TODO err check 
	list_absolute_path_of_command[i] = NULL;
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
	// TODO
	// malloc
	return (v->virtual_argv);
}
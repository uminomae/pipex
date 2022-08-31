/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exe_make_v_argv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:13 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/01 00:55:55 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**split_virtual_argv_from_real_argv(t_pipex *pipex,	\
											char *command_from_argv)
{
	char	**virtual_argv;

	if (command_from_argv == NULL)
		exit_with_error_child_process(pipex, "argv");
	virtual_argv = ft_split(command_from_argv, ' ');
	if (virtual_argv == NULL)
		exit_with_error_child_process(pipex, "ft_split");
	pipex->v_argv.command_name = virtual_argv[0];
	return (virtual_argv);
}

char	**join_file_and_directry_name_to_get_absolute_path(t_pipex *pipex, \
									char **list_of_directry, char *command_name)
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
		list_absolute_path_of_command[i] = \
								ft_strjoin(list_of_directry[i], command_name);
		if (list_absolute_path_of_command == NULL)
			exit_with_error_child_process(pipex, "ft_strjoin");
		i++;
	}
	list_absolute_path_of_command[i] = NULL;
	return (list_absolute_path_of_command);
}

size_t	get_index_accessible_path(t_pipex *pipex, \
									char **list_absolute_path_of_command)
{
	size_t	i;

	i = 0;
	while (list_absolute_path_of_command[i] != NULL)
	{
		if (access(list_absolute_path_of_command[i], R_OK) == 0)
			return (i);
		i++;
	}
	ft_putstr_fd(" command not found: ", 2);
	ft_putendl_fd(pipex->v_argv.command_name, 2);
	set_free_together(pipex);
	_exit(EXIT_FAILURE);
	return (-1);
}

char	**switch_first_argv_to_absolute_path(t_pipex *pipex, \
												t_v_argv *v, size_t index)
{
	void		*tmp;

	tmp = v->virtual_argv[0];
	v->virtual_argv[0] = ft_strdup(v->list_absolute_path_of_command[index]);
	free(tmp);
	if (v->virtual_argv[0] == NULL)
		exit_with_error_child_process(pipex, "ft_split");
	return (v->virtual_argv);
}

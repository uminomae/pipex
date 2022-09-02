/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:16 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/02 18:07:15 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(t_pipex *pipex, char *command_from_argv)
{
	char		**virtual_argv;
	t_v_argv	*v;

	v = &pipex->v_argv;
	get_path_from_env_and_make_list(pipex, v);
	virtual_argv = make_virtual_argv(pipex, v, command_from_argv);
	execve(virtual_argv[0], virtual_argv, pipex->env);
}

//Get the path from the environment variable and make a list
void	get_path_from_env_and_make_list(t_pipex *pipex, t_v_argv *v)
{
	size_t		path_line;

	path_line = get_path_line_from_env(pipex);
	v->temp_devided_list = \
					split_list_of_directry_from_path_line(pipex, path_line);
	v->list_of_directry = \
					join_slash_path_of_directry(pipex, v->temp_devided_list);
}

//Create an accessible absolute path from environment var and arg
char	**make_virtual_argv(t_pipex *pipex, t_v_argv *v, \
							char *command_from_argv)
{
	int	index;

	v->virtual_argv = \
			split_virtual_argv_from_real_argv(pipex, command_from_argv);
	v->list_absolute_path_of_command = \
					join_file_and_directry_name_to_get_absolute_path(\
						pipex, v->list_of_directry, v->virtual_argv[0]);
	index = get_index_accessible_path(v->list_absolute_path_of_command);
	if (index == -1)
		exit_with_error(pipex, "access()");
	v->virtual_argv = switch_first_argv_to_absolute_path(pipex, v, index);
	return (v->virtual_argv);
}

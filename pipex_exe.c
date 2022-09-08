/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:31 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/08 15:04:02 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//static void	duplicate_to_standard_in_out(\
//			t_v_argv *v_argv, int fd_for_read, int fd_for_write);
//static void	x_dup2(t_v_argv *v_argv, int file, int fd);
static void	get_path_from_env_and_make_list(t_pipex *pipex, t_v_argv *v);
static char	**make_virtual_argv(\
				t_pipex *pipex, t_v_argv *v, char *command_from_argv);

char	**get_virtual_argv(\
	t_pipex *pipex, char *command_from_argv)
{
	char		**virtual_argv;

	get_path_from_env_and_make_list(pipex, &pipex->v_argv);
	virtual_argv = make_virtual_argv(pipex, &pipex->v_argv, command_from_argv);
	return (virtual_argv);
}

//Get the path from the environment variable and make a list
static void	get_path_from_env_and_make_list(t_pipex *pipex, t_v_argv *v)
{
	size_t		path_line;

	path_line = get_path_line_from_env(\
					pipex->env, WORD_FIND_PATH, ft_strlen(WORD_FIND_PATH));
	v->temp_devided_list = \
					split_list_of_directry_from_path_line(pipex, path_line);
	v->list_of_directry = \
					join_slash_path_of_directry(pipex, v->temp_devided_list);
}

//Create an accessible absolute path from environment var and arg
static char	**make_virtual_argv(\
				t_pipex *pipex, t_v_argv *v, char *command_from_argv)
{
	int	index;

	v->virtual_argv = \
			split_virtual_argv_from_real_argv(pipex, command_from_argv);
	v->list_absolute_path_of_command = \
					join_file_and_directry_name_to_get_absolute_path(\
						pipex, v->list_of_directry, v->virtual_argv[0]);
	index = get_index_accessible_path(v->list_absolute_path_of_command);
	if (index == ERR_NUM)
		exit_with_error(&pipex->v_argv, ERR_MSG_ACCESS);
	v->virtual_argv = switch_first_argv_to_absolute_path(pipex, v, index);
	return (v->virtual_argv);
}

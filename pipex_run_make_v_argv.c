/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_make_v_argv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:13 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/08 16:07:38 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**split_virtual_argv_from_real_argv(\
									t_pipex *pipex,	char *command_from_argv);
static char	**join_file_and_directry_name_to_get_absolute_path(\
				t_pipex *pipex, char **list_of_directry, char *command_name);
static int	get_index_accessible_path(char **list_absolute_path_of_command);
static char	**switch_first_argv_to_absolute_path(\
								t_pipex *pipex, t_v_argv *v, size_t index);
								
char	**make_virtual_argv(\
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

static char	**split_virtual_argv_from_real_argv(\
									t_pipex *pipex,	char *command_from_argv)
{
	char	**virtual_argv;

	if (command_from_argv == NULL)
		ft_putendl_fd(ERR_MSG_NO_CMD, STDERR_FILENO);
	virtual_argv = \
		x_split(&pipex->v_argv, command_from_argv, ' ');
	return (virtual_argv);
}

static char	**join_file_and_directry_name_to_get_absolute_path(\
				t_pipex *pipex, char **list_of_directry, char *command_name)
{
	char	**list_absolute_path_of_command;
	size_t	i;
	size_t	num;

	num = scale_list_including_null(list_of_directry);
	list_absolute_path_of_command = \
				x_malloc(&pipex->v_argv, sizeof(char *) * num);
	i = 0;
	while (list_of_directry[i] != NULL)
	{
		list_absolute_path_of_command[i] = \
			x_strjoin(\
				&pipex->v_argv, list_of_directry[i], command_name);
		i++;
	}
	list_absolute_path_of_command[i] = NULL;
	return (list_absolute_path_of_command);
}

static int	get_index_accessible_path(char **list_absolute_path_of_command)
{
	int	i;

	i = 0;
	while (list_absolute_path_of_command[i] != NULL)
	{
		if (access(list_absolute_path_of_command[i], R_OK) == 0)
			return (i);
		i++;
	}
	return (ERR_NUM);
}

static char	**switch_first_argv_to_absolute_path(\
								t_pipex *pipex, t_v_argv *v, size_t index)
{
	void	*tmp;

	tmp = v->virtual_argv[ABS_PATH_CMD];
	v->virtual_argv[ABS_PATH_CMD] = \
				ft_strdup(v->list_absolute_path_of_command[index]);
	free(tmp);
	if (v->virtual_argv[ABS_PATH_CMD] == NULL)
		exit_with_error(&pipex->v_argv, ERR_MSG_STRDUP);
	return (v->virtual_argv);
}

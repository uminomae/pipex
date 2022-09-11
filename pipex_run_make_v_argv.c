/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_make_v_argv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:13 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/11 17:51:10 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**split_virtual_argv_from_real_argv(\
									t_pipex *pipex,	char *command_from_argv);
static char	**join_file_and_directory_name_to_get_absolute_path(\
				t_pipex *pipex, char **list_of_directory, char *command_name);
static int	get_index_accessible_path(char **list_absolute_path_of_command);
static char	**switch_first_argv_to_absolute_path(\
								t_pipex *pipex, t_arg *v, size_t index);

char	**make_virtual_argv(\
				t_pipex *pipex, t_arg *v, char *command_from_argv)
{
	int		index;

	v->virtual_argv = \
			split_virtual_argv_from_real_argv(pipex, command_from_argv);
	v->list_absolute_path_of_command = \
			join_file_and_directory_name_to_get_absolute_path(\
				pipex, v->list_of_directory, v->virtual_argv[0]);
	index = get_index_accessible_path(v->list_absolute_path_of_command);
	if (index == ERR_NUM)
		exit_with_error(pipex, command_from_argv, TYPE_CMD_NOT_FOUND);
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
			x_split(pipex, command_from_argv, DELIMITER_CMD);
	return (virtual_argv);
}

static char	**join_file_and_directory_name_to_get_absolute_path(\
				t_pipex *pipex, char **list_of_directory, char *command_name)
{
	char	**list_absolute_path_of_command;
	size_t	i;
	size_t	num;
	char	*abs_sign;

	num = scale_list_including_null(list_of_directory);
	list_absolute_path_of_command = \
				x_malloc(pipex, sizeof(char *) * num);
	i = 0;
	while (list_of_directory[i] != NULL)
	{
		abs_sign = ft_strchr(command_name, SIGN_ABS_PATH);
		if (abs_sign == NOT_FOUND)
			list_absolute_path_of_command[i] = \
				x_strjoin(\
					pipex, list_of_directory[i], command_name);
		else
			list_absolute_path_of_command[i] = x_strdup(pipex, command_name);
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
								t_pipex *pipex, t_arg *v, size_t index)
{
	void	*tmp;

	tmp = v->virtual_argv[ABS_PATH_CMD];
	v->virtual_argv[ABS_PATH_CMD] = \
				x_strdup(pipex, v->list_absolute_path_of_command[index]);
	free(tmp);
	if (v->virtual_argv[ABS_PATH_CMD] == NULL)
		exit_with_error(pipex, ERR_MSG_STRDUP, 1);
	return (v->virtual_argv);
}

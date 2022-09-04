/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_make_v_argv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:13 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/04 22:45:01 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**split_virtual_argv_from_real_argv(\
									t_pipex *pipex,	char *command_from_argv)
{
	char	**virtual_argv;

	if (command_from_argv == NULL)
		ft_putendl_fd(ERR_MSG_NO_CMD, STDERR_FILENO);
	virtual_argv = \
		split_str_and_check_for_null(&pipex->v_argv, command_from_argv, ' ');
	return (virtual_argv);
}

char	**join_file_and_directry_name_to_get_absolute_path(\
				t_pipex *pipex, char **list_of_directry, char *command_name)
{
	char	**list_absolute_path_of_command;
	size_t	i;
	size_t	num;

	num = scale_list_including_null(list_of_directry);
	list_absolute_path_of_command = \
				malloc_and_check_for_null(&pipex->v_argv, sizeof(char *) * num);
	i = 0;
	while (list_of_directry[i] != NULL)
	{
		list_absolute_path_of_command[i] = \
			join_str_and_check_for_null(\
				&pipex->v_argv, list_of_directry[i], command_name);
		i++;
	}
	list_absolute_path_of_command[i] = NULL;
	return (list_absolute_path_of_command);
}

int	get_index_accessible_path(char **list_absolute_path_of_command)
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

char	**switch_first_argv_to_absolute_path(\
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

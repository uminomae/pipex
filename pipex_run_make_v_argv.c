/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_make_v_argv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:13 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/14 17:06:29 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**split_cmd_name_and_option(t_pipex *pipex,	char *cmd_name);
static char	**join_to_get_absolute_path(\
				t_pipex *pipex, char **list_of_directory, char *cmd_name);
static int	get_index_accessible_path(char **list_abs_path_cmd);
static char	**switch_first_argv(t_pipex *pipex, t_arg *v, size_t index);

char	**make_virtual_argv(t_pipex *pipex, t_arg *v, char *cmd_name)
{
	int		index;

	v->virtual_argv = split_cmd_name_and_option(pipex, cmd_name);
	v->list_abs_path_cmd = join_to_get_absolute_path(\
				pipex, v->list_of_directory, v->virtual_argv[0]);
	index = get_index_accessible_path(v->list_abs_path_cmd);
	if (index == ERR_NUM)
		exit_with_error(pipex, cmd_name, TYPE_CMD_NOT_FOUND, true);
	v->virtual_argv = switch_first_argv(pipex, v, index);
	return (v->virtual_argv);
}

static char	**split_cmd_name_and_option(t_pipex *pipex,	char *cmd_name)
{
	char	**virtual_argv;

	if (cmd_name == NULL)
		exit_with_error(pipex, ERR_MSG_CMD_NULL, TYPE_CMD_NOT_FOUND, true);
	if (*cmd_name == NULL_CHAR)
		exit_with_error(pipex, ERR_MSG_CMD_NULL_CHAR, TYPE_CMD_NOT_FOUND, true);
	virtual_argv = x_split(pipex, cmd_name, DELIMITER_CMD);
	return (virtual_argv);
}

// TODO　相対パスのif分岐
static char	**join_to_get_absolute_path(\
				t_pipex *pipex, char **list_of_directory, char *cmd_name)
{
	char	**list_abs_path;
	size_t	i;
	size_t	num;
	char	*abs_sign;

	num = scale_list_including_null(list_of_directory);
	list_abs_path = x_malloc(pipex, sizeof(char *) * num);
	i = 0;
	while (list_of_directory[i] != NULL)
	{
		abs_sign = ft_strchr(cmd_name, SIGN_ABS_PATH);
		if (abs_sign == NOT_FOUND)
			list_abs_path[i] = x_strjoin(pipex, list_of_directory[i], cmd_name);
		else
			list_abs_path[i] = x_strdup(pipex, cmd_name);
		i++;
	}
	list_abs_path[i] = NULL;
	return (list_abs_path);
}

static int	get_index_accessible_path(char **list_abs_path)
{
	int	i;

	i = 0;
	while (list_abs_path[i] != NULL)
	{
		if (access(list_abs_path[i], X_OK) == 0)
			return (i);
		i++;
	}
	return (ERR_NUM);
}

static char	**switch_first_argv(t_pipex *pipex, t_arg *v, size_t index)
{
	void	*tmp;

	tmp = v->virtual_argv[ABS_PATH_CMD];
	v->virtual_argv[ABS_PATH_CMD] =	x_strdup(pipex, v->list_abs_path_cmd[index]);
	free(tmp);
	if (v->virtual_argv[ABS_PATH_CMD] == NULL)
		exit_with_error(pipex, ERR_MSG_STRDUP, TYPE_PERROR, true);
	return (v->virtual_argv);
}

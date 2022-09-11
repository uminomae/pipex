/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_get_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/11 17:49:43 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	get_path_line_from_env(char **env, char *str, size_t len);
static char		**split_list_of_directory_from_path_line(\
										t_pipex *pipex, size_t path_index);
static char	**trim_unnecessary_characters(\
				t_pipex *pipex, char **temp_divided_list, char *trim_str);
static char		**join_slash_path_of_directory(\
					t_pipex *pipex, char **temp_divided_list);

void	get_path(t_pipex *pipex, t_arg *v)
{
	size_t		path_line;

	path_line = get_path_line_from_env(\
					environ, WORD_FIND_PATH, ft_strlen(WORD_FIND_PATH));
	v->temp_divided_list = \
					split_list_of_directory_from_path_line(pipex, path_line);
	v->list_of_directory = \
					join_slash_path_of_directory(pipex, v->temp_divided_list);
}

static size_t	get_path_line_from_env(char **env, char *str, size_t len)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], str, len) == SAME_STRING)
			return (i);
		i++;
	}
	return (NOT_FIND);
}

static char	**split_list_of_directory_from_path_line(\
					t_pipex *pipex, size_t path_index)
{
	char	**temp_divided_list;

	temp_divided_list = \
		x_split(\
			pipex, environ[path_index], DELIMITER_PATH);
	temp_divided_list = \
		trim_unnecessary_characters(pipex, temp_divided_list, WORD_FIND_PATH);
	return (temp_divided_list);
}

static char	**trim_unnecessary_characters(\
				t_pipex *pipex, char **temp_divided_list, char *trim_str)
{
	size_t	trim_len;
	size_t	new_string_len;
	void	*tmp;

	trim_len = ft_strlen(trim_str);
	new_string_len = ft_strlen(temp_divided_list[FIRST_LINE]) - trim_len;
	tmp = temp_divided_list[FIRST_LINE];
	temp_divided_list[FIRST_LINE] = x_substr(pipex, \
			temp_divided_list[FIRST_LINE] + trim_len, 0, new_string_len);
	free(tmp);
	return (temp_divided_list);
}

static char	**join_slash_path_of_directory(\
				t_pipex *pipex, char **temp_divided_list)
{
	char	**list_of_directory;
	size_t	i;
	size_t	list_size;

	list_size = scale_list_including_null(temp_divided_list);
	list_of_directory = \
		x_malloc(pipex, sizeof(char *) * list_size);
	i = 0;
	while (temp_divided_list[i] != NULL)
	{
		list_of_directory[i] = \
			x_strjoin(\
				pipex, temp_divided_list[i], STR_SLASH);
		i++;
	}
	list_of_directory[i] = NULL;
	return (list_of_directory);
}

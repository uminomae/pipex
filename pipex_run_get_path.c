/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_get_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/09 09:17:21 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	get_path_line_from_env(char **env, char *str, size_t len);
static char	**split_list_of_directry_from_path_line(\
										t_pipex *pipex, size_t path_index);
static char	**trim_unnecessary_characters(\
							char **temp_devided_list, char *trim_str);
static char	**join_slash_path_of_directry(t_pipex *pipex, char **temp_devided_list);


void	get_path_from_env_and_make_list(t_pipex *pipex, t_v_argv *v)
{
	size_t		path_line;

	path_line = get_path_line_from_env(\
					environ, WORD_FIND_PATH, ft_strlen(WORD_FIND_PATH));
					//pipex->env, WORD_FIND_PATH, ft_strlen(WORD_FIND_PATH));
	v->temp_devided_list = \
					split_list_of_directry_from_path_line(pipex, path_line);
	v->list_of_directry = \
					join_slash_path_of_directry(pipex, v->temp_devided_list);
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


static char	**split_list_of_directry_from_path_line(\
					t_pipex *pipex, size_t path_index)
{
	char	**temp_devided_list;

	temp_devided_list = \
		x_split(\
			&pipex->v_argv, environ[path_index], DELIMITER_PATH);
			//&pipex->v_argv, pipex->env[path_index], DELIMITER_PATH);
	temp_devided_list = \
		trim_unnecessary_characters(temp_devided_list, WORD_FIND_PATH);
	return (temp_devided_list);
}

static char	**trim_unnecessary_characters(\
							char **temp_devided_list, char *trim_str)
{
	size_t	trim_len;
	size_t	new_string_len;
	void	*tmp;

	trim_len = ft_strlen(trim_str);
	new_string_len = ft_strlen(temp_devided_list[FIRST_LINE]) - trim_len;
	tmp = temp_devided_list[FIRST_LINE];
	temp_devided_list[FIRST_LINE] = \
		ft_substr(temp_devided_list[FIRST_LINE] + trim_len, 0, new_string_len);
	free(tmp);
	return (temp_devided_list);
}


static char	**join_slash_path_of_directry(t_pipex *pipex, char **temp_devided_list)
{
	char	**list_of_directry;
	size_t	i;
	size_t	list_size;

	list_size = scale_list_including_null(temp_devided_list);
	list_of_directry = \
		x_malloc(&pipex->v_argv, sizeof(char *) * list_size);
	i = 0;
	while (temp_devided_list[i] != NULL)
	{
		list_of_directry[i] = \
			x_strjoin(\
				&pipex->v_argv, temp_devided_list[i], STR_SLASH);
		i++;
	}
	list_of_directry[i] = NULL;
	return (list_of_directry);
}

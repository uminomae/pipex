/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_get_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/04 09:13:10 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**trim_unnecessary_characters(\
							char **temp_devided_list, char *trim_str);

size_t	get_path_line_from_env(char **env, char *str, size_t len)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], str, len) == 0)
			return (i);
		i++;
	}
	return (0);
}

char	**split_list_of_directry_from_path_line(\
					t_pipex *pipex, size_t path_index)
{
	char	**temp_devided_list;

	temp_devided_list = \
		split_str_and_also_check_for_null(&pipex->v_argv, pipex->env[path_index], ':');
	temp_devided_list = \
		trim_unnecessary_characters(temp_devided_list, "PATH=");
	return (temp_devided_list);
}

static char	**trim_unnecessary_characters(\
							char **temp_devided_list, char *trim_str)
{
	size_t	trim_len;
	size_t	new_string_len;
	void	*tmp;

	trim_len = ft_strlen(trim_str);
	new_string_len = ft_strlen(temp_devided_list[0]) - trim_len;
	tmp = temp_devided_list[0];
	temp_devided_list[0] = \
			ft_substr(temp_devided_list[0] + trim_len, 0, new_string_len);
	free(tmp);
	return (temp_devided_list);
}

char	**join_slash_path_of_directry(t_pipex *pipex, char **temp_devided_list)
{
	char	**list_of_directry;
	size_t	i;
	size_t	list_size;

	list_size = scale_list_including_null(temp_devided_list);
	list_of_directry = \
		malloc_and_also_check_for_null(&pipex->v_argv, sizeof(char *) * list_size);
	i = 0;
	while (temp_devided_list[i] != NULL)
	{
		list_of_directry[i] = \
					join_str_and_also_check_for_null(&pipex->v_argv, temp_devided_list[i], "/");
		i++;
	}
	list_of_directry[i] = NULL;
	return (list_of_directry);
}

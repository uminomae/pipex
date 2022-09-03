/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exe_get_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/03 22:20:45 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include "pipex.h"
//static char	**split_str(t_v_argv *v_argv,char **env, \
//										size_t path_index);
static char	**trim_unnecessary_characters_at_the_beginning(\
											char	**temp_devided_list);

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

char	**split_list_of_directry_from_path_line(t_pipex *pipex, \
												size_t path_index)
{
	char	**temp_devided_list;

	temp_devided_list = \
		split_str(&pipex->v_argv, pipex->env, path_index);
	temp_devided_list = trim_unnecessary_characters_at_the_beginning(\
		temp_devided_list);
	return (temp_devided_list);
}

static char	**trim_unnecessary_characters_at_the_beginning(\
											char	**temp_devided_list)
{
	size_t	trim_len;
	size_t	new_string_len;
	void	*tmp;

	trim_len = ft_strlen("PATH=");
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
	list_of_directry = malloc_and_check_for_null(&pipex->v_argv, \
												sizeof(char *) * list_size);
	i = 0;
	while (temp_devided_list[i] != NULL)
	{
		list_of_directry[i] = join_str(&pipex->v_argv, temp_devided_list[i], "/");
		i++;
	}
	list_of_directry[i] = NULL;
	return (list_of_directry);
}
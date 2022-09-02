/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exe_get_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/02 17:03:15 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	get_path_line_from_env(t_pipex *pipex)
{
	size_t	i;

	i = 0;
	while (pipex->env[i] != NULL)
	{
		if (ft_strncmp(pipex->env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (0);
}

char	**split_list_of_directry_from_path_line(t_pipex *pipex, \
												size_t path_index)
{
	size_t	trim_len;
	char	**temp_devided_list;
	void	*tmp;

	temp_devided_list = ft_split(pipex->env[path_index], ':');
	if (temp_devided_list == NULL)
		exit_with_error(pipex, "ft_split()");
	trim_len = ft_strlen("PATH=");
	tmp = temp_devided_list[0];
	temp_devided_list[0] = ft_substr(temp_devided_list[0] + trim_len, 0, \
										ft_strlen(temp_devided_list[0]));
	free(tmp);
	return (temp_devided_list);
}

char	**join_slash_path_of_directry(t_pipex *pipex, char **temp_devided_list)
{
	char	**list_of_directry;
	size_t	i;
	size_t	list_size;

	list_of_directry = NULL;
	list_size = scale_list_including_null(temp_devided_list);
	list_of_directry = malloc(sizeof(char *) * list_size);
	if (list_of_directry == NULL)
		exit_with_error(pipex, "malloc()");
	i = 0;
	while (temp_devided_list[i] != NULL)
	{
		list_of_directry[i] = ft_strjoin(temp_devided_list[i], "/");
		if (list_of_directry == NULL)
			exit_with_error(pipex, "ft_strjoin()");
		i++;
	}
	list_of_directry[i] = NULL;
	return (list_of_directry);
}

size_t	scale_list_including_null(char **list)
{
	size_t	count;

	count = 0;
	while (list[count] != NULL)
		count++;
	count++;
	return (count);
}

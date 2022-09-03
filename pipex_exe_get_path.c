/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exe_get_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/03 21:54:24 by hioikawa         ###   ########.fr       */
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

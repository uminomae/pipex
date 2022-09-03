/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exe_get_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/03 21:33:15 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
//static char	**ft_split_string_at_colon(t_v_argv *v_argv,char **env, size_t path_index);
//static char	**trim_unnecessary_characters_at_the_beginning(char	**temp_devided_list);

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

	//list_of_directry = NULL;
	// rename scale nad alloc
	list_size = scale_list_including_null(temp_devided_list);
	list_of_directry = malloc(sizeof(char *) * list_size);
	if (list_of_directry == NULL)
		exit_with_error(&pipex->v_argv, "malloc()");
	i = 0;
	while (temp_devided_list[i] != NULL)
	{
		// rename join
		list_of_directry[i] = ft_strjoin(temp_devided_list[i], "/");
		if (list_of_directry == NULL)
			exit_with_error(&pipex->v_argv, "ft_strjoin()");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_x_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/10 14:25:53 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**x_split(\
					t_pipex *pipex, char *str, char delimiter)
{
	char	**ret;

	ret = ft_split(str, delimiter);
	if (ret == NULL)
		exit_with_error(pipex, ERR_MSG_SPLIT);
	return (ret);
}

void	*x_malloc(t_pipex *pipex, size_t size)
{
	void	*ret;

	ret = malloc(sizeof(char *) * size);
	if (ret == NULL)
		exit_with_error(pipex, ERR_MSG_MALLOC);
	return (ret);
}

char	*x_strjoin(\
				t_pipex *pipex, char *str, char *str_to_add)
{
	char	*ret;

	ret = ft_strjoin(str, str_to_add);
	if (ret == NULL)
		exit_with_error(pipex, ERR_MSG_STRJOIN);
	return (ret);
}

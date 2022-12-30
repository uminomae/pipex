/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_x_libft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/12/30 22:37:19 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**x_split(t_pipex *pipex, char *str, char delimiter)
{
	char	**ret;

	ret = ft_split(str, delimiter);
	if (ret == NULL)
		exit_with_error(pipex, ERR_MSG_SPLIT, TYPE_FT, true);
	return (ret);
}

void	*x_malloc(t_pipex *pipex, size_t size)
{
	void	*ret;

	ret = malloc(sizeof(void *) * size);
	if (ret == NULL)
		exit_with_error(pipex, ERR_MSG_MALLOC, TYPE_FT, true);
	return (ret);
}

char	*x_strjoin(t_pipex *pipex, char *str, char *str_to_add)
{
	char	*ret;

	ret = ft_strjoin(str, str_to_add);
	if (ret == NULL)
		exit_with_error(pipex, ERR_MSG_STRJOIN, TYPE_FT, true);
	return (ret);
}

char	*x_strdup(t_pipex *pipex, char *str)
{
	char	*ret;

	ret = ft_strdup(str);
	if (ret == NULL)
		exit_with_error(pipex, ERR_MSG_STRDUP, TYPE_FT, true);
	return (ret);
}

char	*x_substr(t_pipex *pipex, char *str, int start, size_t len)
{
	char	*ret;

	ret = ft_substr(str, start, len);
	if (ret == NULL)
		exit_with_error(pipex, ERR_MSG_SUBSTR, TYPE_FT, true);
	return (ret);
}

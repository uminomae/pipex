/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_x_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/08 16:41:11 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**x_split(\
					t_v_argv *v_argv, char *str, char delimiter)
{
	char	**ret;

	ret = ft_split(str, delimiter);
	if (ret == NULL)
		exit_with_error(v_argv, ERR_MSG_SPLIT);
	return (ret);
}

void	*x_malloc(t_v_argv *v_argv, size_t size)
{
	void	*ret;

	ret = malloc(sizeof(char *) * size);
	if (ret == NULL)
		exit_with_error(v_argv, ERR_MSG_MALLOC);
	return (ret);
}

char	*x_strjoin(\
				t_v_argv *v_argv, char *str, char *str_to_add)
{
	char	*ret;

	ret = ft_strjoin(str, str_to_add);
	if (ret == NULL)
		exit_with_error(v_argv, ERR_MSG_STRJOIN);
	return (ret);
}


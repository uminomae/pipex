/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/05 03:53:57 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**split_str_and_check_for_null(\
					t_v_argv *v_argv, char *str, char delimiter)
{
	char	**ret;

	ret = ft_split(str, delimiter);
	if (ret == NULL)
		exit_with_error(v_argv, ERR_MSG_SPLIT);
	return (ret);
}

void	*malloc_and_check_for_null(t_v_argv *v_argv, size_t size)
{
	void	*ret;

	ret = malloc(sizeof(char *) * size);
	if (ret == NULL)
		exit_with_error(v_argv, ERR_MSG_MALLOC);
	return (ret);
}

char	*join_str_and_check_for_null(\
				t_v_argv *v_argv, char *str, char *str_to_add)
{
	char	*ret;

	ret = ft_strjoin(str, str_to_add);
	if (ret == NULL)
		exit_with_error(v_argv, ERR_MSG_STRJOIN);
	return (ret);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/04 09:12:14 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**split_str_and_also_check_for_null(t_v_argv *v_argv, char *str, char at_that)
{
	char	**ret;

	ret = ft_split(str, at_that);
	if (ret == NULL)
		exit_with_error(v_argv, "ft_split()");
	return (ret);
}

void	*malloc_str_and_also_check_for_null(t_v_argv *v_argv, size_t size)
{
	void	*ret;

	ret = malloc(sizeof(char *) * size);
	if (ret == NULL)
		exit_with_error(v_argv, "malloc()");
	return (ret);
}

char	*join_str_and_also_check_for_null(t_v_argv *v_argv, char *str, char *str_to_add)
{
	char	*ret;

	ret = ft_strjoin(str, str_to_add);
	if (ret == NULL)
		exit_with_error(v_argv, "ft_strjoin()");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/12/31 01:06:55 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	scale_list_including_null(char **list)
{
	size_t	count;

	count = 0;
	while (list[count] != NULL)
		count++;
	count++;
	return (count);
}

void	close_both_fd(t_pipex *pipex, const int *const fd)
{
	x_close(pipex, fd[WRITE]);
	x_close(pipex, fd[READ]);
}

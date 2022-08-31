/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:50:49 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/01 00:50:50 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	close_unused_file_descriptor(t_pipex *pipex, int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == -1)
		exit_with_error_child_process(pipex, "close");
	return (ret);
}

void	close_both_pipe(t_pipex *pipex)
{
	close_unused_file_descriptor(pipex, pipex->pipe_fd[READ]);
	close_unused_file_descriptor(pipex, pipex->pipe_fd[WRITE]);
}

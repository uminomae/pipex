/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_x_sys_call1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/15 18:28:01 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	x_pipe(t_pipex *pipex, int pipe_fd[2])
{
	int	ret;

	ret = pipe(pipe_fd);
	if (ret == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_PIPE, TYPE_PERROR, true);
}

pid_t	x_fork(t_pipex *pipex)
{
	pid_t	ret;

	ret = fork();
	if (ret == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_FORK, TYPE_PERROR, true);
	return (ret);
}

void	x_dup2(t_pipex *pipex, int fd1, int fd2)
{
	int	ret;

	ret = dup2(fd1, fd2);
	if (ret == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_DUP2, TYPE_PERROR, true);
}

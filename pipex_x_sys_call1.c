/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_x_sys_call.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/10 14:47:04 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	x_pipe(int pipe_fd[2], t_pipex *pipex)
{
	int	ret;

	ret = pipe(pipe_fd);
	if (ret == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_PIPE, 1);
}

pid_t	x_fork(t_pipex *pipex)
{
	pid_t	ret;

	ret = fork();
	if (ret == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_FORK, 1);
	return (ret);
}

void	x_dup2(t_pipex *pipex, int file, int fd)
{
	int	ret;

	ret = dup2(file, fd);
	if (ret == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_DUP2, 1);
}
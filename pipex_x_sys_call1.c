/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_x_sys_call1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/15 20:48:53 by uminomae         ###   ########.fr       */
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

void	x_close(t_pipex *pipex, int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_CLOSE, TYPE_PERROR, true);
}

void	x_execve(t_pipex *pipex, char **virtual_argv)
{
	int	ret;

	ret = execve(virtual_argv[ABS_PATH_CMD], virtual_argv, environ);
	if (ret == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_EXCECVE, TYPE_PERROR, true);
}
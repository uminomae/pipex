/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_x_system_call.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/08 16:48:04 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	x_pipe(int pipe_fd[2], t_v_argv *v_argv)
{
	int	ret;

	ret = pipe(pipe_fd);
	if (ret == ERR_NUM)
		exit_with_error(v_argv, ERR_MSG_PIPE);
}

pid_t	x_fork(t_pipex *pipex)
{
	pid_t	ret;

	ret = fork();
	if (ret == ERR_NUM)
	{
		close_both_pipe(&pipex->v_argv, pipex->pipe_list.head->pipe_fd);
		exit_with_error(&pipex->v_argv, ERR_MSG_FORK);
	}
	return (ret);
}

void	x_dup2(t_v_argv *v_argv, int file, int fd)
{
	int	ret;

	ret = dup2(file, fd);
	if (ret == ERR_NUM)
		exit_with_error(v_argv, ERR_MSG_DUP2);
}

void	x_close(t_v_argv *v_argv, int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == ERR_NUM)
		exit_with_error(v_argv, ERR_MSG_CLOSE);
}

void	x_waitpid(t_v_argv *v_argv, pid_t process_id)
{
	pid_t	ret;
	int		child_status;

	ret = waitpid(process_id, &child_status, GROUP_OF_CALLER);
	if (ret == ERR_NUM)
		exit_with_error(v_argv, ERR_MSG_WAITPID);
}

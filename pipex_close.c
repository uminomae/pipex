/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:20 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/02 16:03:30 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	x_close(t_v_argv *v_argv, int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == ERR_NUM)
		exit_with_error(v_argv, ERR_MSG_CLOSE);
}

void	close_both_pipe(t_v_argv *v_argv, const int *const pipe_fd)
{
	x_close(v_argv, pipe_fd[READ]);
	x_close(v_argv, pipe_fd[WRITE]);
}
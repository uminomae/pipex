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

void	close_unused_file_descriptor(t_v_argv *v_argv, int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == ERR_NUM)
		exit_with_error(v_argv, ERR_MSG_CLOSE);
}

void	close_both_pipe(t_v_argv *v_argv, const int *const pipe_fd)
{
	close_unused_file_descriptor(v_argv, pipe_fd[READ]);
	close_unused_file_descriptor(v_argv, pipe_fd[WRITE]);
}

void	safe_free(char **malloc_ptr)
{
	free(*malloc_ptr);
	*malloc_ptr = NULL;
}

void	exit_successfully(t_v_argv *v_argv)
{
	free_struct(v_argv);
	exit(EXIT_FAILURE);
}

void	exit_with_error(t_v_argv *v_argv, char *str)
{
	free_struct(v_argv);
	perror(str);
	exit(EXIT_FAILURE);
}

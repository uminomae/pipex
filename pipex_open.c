/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:31 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/10 16:42:59 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	open_read_file(int *fd, char *argv);
static void	open_write_file(int *fd, char *argv);

void	open_case_here_doc(t_pipex *pipex, int argc, char **argv, int *file_fd)
{
	size_t	last_index;

	last_index = argc - 1;
	open_write_file(file_fd, argv[last_index]);
	if (file_fd[WRITE] == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_OPEN, 1);
}

void	open_files(\
			t_pipex *pipex, int argc, char *const *argv, int *file_fd)
{
	size_t	last_index;

	last_index = argc - 1;
	open_read_file(file_fd, argv[FILE_FOR_READ]);
	open_write_file(file_fd, argv[last_index]);
	if (file_fd[READ] == ERR_NUM || file_fd[WRITE] == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_OPEN, 1);
}

static void	open_read_file(int *file_fd, char *argv)
{
	file_fd[READ] = open(argv, O_RDONLY | O_CLOEXEC);
}

//file[WRITE] is like a chmod 644 
static void	open_write_file(int *file_fd, char *argv)
{
	file_fd[WRITE] = open(argv, O_WRONLY | O_CLOEXEC | O_CREAT | O_TRUNC, \
							S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

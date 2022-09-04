/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_open.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:31 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/04 13:49:16 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	open_read_file(int *fd, char *argv);
static void	open_write_file(int *fd, char *argv);

void	open_files_on_purpose(\
			t_pipex *pipex, char *const *argv, int *file_fd, int read_or_write)
{
	if (read_or_write == READ)
		open_read_file(file_fd, argv[1]);
	else if (read_or_write == WRITE)
		open_write_file(file_fd, argv[pipex->argc - 1]);
	if (file_fd[READ] == -1 | file_fd[WRITE] == -1)
		exit_with_error(&pipex->v_argv, "open()");
}

static void	open_read_file(int *fd, char *argv)
{
	fd[READ] = open(argv, O_RDONLY | O_CLOEXEC, 0);
}

//file[WRITE] is like a chmod 644 
static void	open_write_file(int *fd, char *argv)
{
	fd[WRITE] = open(argv, O_WRONLY | O_CLOEXEC | O_CREAT | O_TRUNC, \
							S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_open.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:31 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/07 01:49:45 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	open_read_file(int *fd, char *argv);
static void	open_write_file(int *fd, char *argv);

//void	open_files_on_purpose(\
//			t_pipex *pipex, char *const *argv, int *file_fd, int read_or_write)
//{
//	size_t	last_arg;

//	last_arg = pipex->argc - SUBTRACT_ONE_BECAUSE_IDX_FROM_0;
//	if (read_or_write == READ)
//		open_read_file(file_fd, argv[FILE_FOR_READ]);
//	else if (read_or_write == WRITE)
//		open_write_file(file_fd, argv[last_arg]);
//	if (file_fd[READ] == ERR_NUM | file_fd[WRITE] == ERR_NUM)
//		exit_with_error(&pipex->v_argv, ERR_MSG_OPEN);
//}

void	open_files(\
			t_pipex *pipex, char *const *argv, int *file_fd)
{
	size_t	last_arg;

	last_arg = pipex->argc - SUBTRACT_ONE_BECAUSE_IDX_FROM_0;
	open_read_file(file_fd, argv[FILE_FOR_READ]);
	open_write_file(file_fd, argv[last_arg]);
	if (file_fd[READ] == ERR_NUM | file_fd[WRITE] == ERR_NUM)
		exit_with_error(&pipex->v_argv, ERR_MSG_OPEN);
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

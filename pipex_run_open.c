/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_open.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:31 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/03 23:35:40 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	open_read_file(int *fd, char *argv);
static void	open_write_file(int *fd, char *argv);



//file[WRITE] is like a chmod 644
	//TODO const
	//char	*const	*argv = (char *const *)pipex->argv;
	//int		*const	fd = pipex->file_fd;
void	open_files_on_purpose(\
				t_v_argv *v_argv, char *const *argv, int *fd, int in_out)
{
	if (in_out == READ)
		open_read_file(fd, argv[1]);
	else if (in_out == WRITE)
		open_write_file(fd, argv[4]);
	if (fd[READ] == -1 | fd[WRITE] == -1)
		exit_with_error(v_argv, "open()");
}

static void	open_read_file(int *fd, char *argv)
{
	fd[READ] = open(argv, O_RDONLY | O_CLOEXEC, 0);
}

static void	open_write_file(int *fd, char *argv)
{
	fd[WRITE] = open(argv, O_WRONLY | O_CLOEXEC | O_CREAT | O_TRUNC, \
							S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

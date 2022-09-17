/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:31 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/15 20:57:34 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	open_normal_case(t_pipex *pipex, int argc, char **argv);
static void	dup_file_fd_std_in_out(t_pipex *pipex);

void	open_files_and_dup(t_pipex *pipex, int argc, char **argv)
{
	if (pipex->is_here_doc == true)
		open_here_doc(pipex, argc, argv);
	else
		open_normal_case(pipex, argc, argv);
	dup_file_fd_std_in_out(pipex);
}

static void	open_normal_case(t_pipex *pipex, int argc, char **argv)
{
	size_t	last_index;

	last_index = argc - 1;
	pipex->file_fd[READ] = open_read_file(pipex, argv[FILE_FOR_READ]);
	pipex->file_fd[WRITE] = open_write_file(pipex, argv[last_index]);
}

int	open_read_file(t_pipex *pipex, char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY | O_CLOEXEC);
	if (fd == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_OPEN, TYPE_PERROR, true);
	return (fd);
}

//file[WRITE] is like a chmod 644 
int	open_write_file(t_pipex *pipex, char *argv)
{
	int	fd;

	fd = open(argv, O_WRONLY | O_CLOEXEC | O_CREAT | O_TRUNC, \
							S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_OPEN, TYPE_PERROR, true);
	return (fd);
}

static void	dup_file_fd_std_in_out(t_pipex *pipex)
{
	x_dup2(pipex, pipex->file_fd[READ], STDIN_FILENO);
	x_dup2(pipex, pipex->file_fd[WRITE], STDOUT_FILENO);
	close_both_fd(pipex, pipex->file_fd);
}

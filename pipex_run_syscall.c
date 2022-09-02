/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_syscall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:31 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/02 13:56:49 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_child_process_by_fork_func(t_pipex *pipex, int i)
{
	pid_t *const	pid = pipex->pid;

	pid[i] = fork();
	if (pid[i] == -1)
	{
		close_both_pipe(pipex);
		exit_with_error_child_process(pipex, "fork");
	}
}

//file[WRITE] is like a chmod 644
void	open_file(t_pipex *pipex, int in_out)
{
	char *const	*argv = (char *const *)pipex->argv;
	int *const	file = pipex->file_fd;

	if (in_out == READ)
		file[READ] = open(argv[1], O_RDONLY | O_CLOEXEC, 0);
	else if (in_out == WRITE)
		file[WRITE] = \
			open(argv[4], O_WRONLY | O_CLOEXEC | O_CREAT | O_TRUNC, \
							S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (file[READ] == -1 | file[WRITE] == -1)
		exit_with_error_child_process(pipex, "open");
}

void	duplicate_to_standard_in_out(t_pipex *pipex, \
							int file_for_reading, int file_for_writing)
{
	int	ret_in;
	int	ret_out;

	ret_in = dup2(file_for_reading, STANDARD_INPUT);
	close_unused_file_descriptor(pipex, file_for_reading);
	if (ret_in == -1)
		exit_with_error_child_process(pipex, "dup2");
	ret_out = dup2(file_for_writing, STANDARD_OUTPUT);
	close_unused_file_descriptor(pipex, file_for_writing);
	if (ret_out == -1)
		exit_with_error_child_process(pipex, "dup2");
}

void	wait_pid_for_child_process(t_pipex *pipex, int i)
{
	pid_t	ret_pid;
	int		child_status;

	ret_pid = waitpid(pipex->pid[i], &child_status, 0);
	if (ret_pid == -1)
		exit_with_error_child_process(pipex, "waitpid");
}

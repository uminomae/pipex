/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/04 13:53:47 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_child_to_file(\
				t_pipex *pipex, char **argv, int read_or_write, int argv_idx)
{
	const int *const	pipe = pipex->pipe_fd;
	int *const			file_fd = pipex->file_fd;
	t_v_argv			*v_argv;
	pid_t				process_id;

	v_argv = &pipex->v_argv;
	process_id = create_child_process_by_fork_func(pipex);
	if (process_id == 0)
	{
		close_unused_file_descriptor(v_argv, pipe[read_or_write]);
		open_files_on_purpose(pipex, argv, file_fd, read_or_write);
		if (read_or_write == READ)
			duplicate_and_execute(\
				pipex, file_fd[READ], pipe[WRITE], argv[argv_idx]);
		else if (read_or_write == WRITE)
			duplicate_and_execute(\
				pipex, pipe[READ], file_fd[WRITE], argv[argv_idx]);
		close_unused_file_descriptor(v_argv, file_fd[read_or_write]);
		exit_successfully(v_argv);
	}
	if (read_or_write == WRITE)
		close_both_pipe(v_argv, pipe);
	wait_pid_for_child_process(v_argv, process_id);
}

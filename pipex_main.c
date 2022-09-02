/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/02 15:52:11 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	begin_pipex(&pipex, argc, argv, env);
	create_pipe_fd(&pipex);
	run_read_side(&pipex, READ);
	run_write_side(&pipex, WRITE);
	return (0);
}

void	begin_pipex(t_pipex *pipex, int argc, char **argv, char **env)
{
	//check_for_valid_value(argc);
	validate_number_of_arguments(argc);
	init_struct(pipex, argc, argv, env);
}

void	create_pipe_fd(t_pipex *pipex)
{
	int	ret;

	ret = pipe(pipex->pipe_fd);
	if (ret == -1)
		exit_with_error_child_process(pipex, "pipe");
}

void	run_read_side(t_pipex *pipex, int i)
{
	const int	*pipe = pipex->pipe_fd;
	int *const	file = pipex->file_fd;

	create_child_process_by_fork_func(pipex, i);
	if (pipex->pid[i] == 0)
	{
		close_unused_file_descriptor(pipex, pipe[i]);
		open_file(pipex, i);
		duplicate_to_standard_in_out(pipex, file[READ], pipe[WRITE]);
		execute_command(pipex, pipex->argv[2]);
		close_unused_file_descriptor(pipex, file[i]);
		exit_successfully_child_process(pipex);
	}
	wait_pid_for_child_process(pipex, i);
}

void	run_write_side(t_pipex *pipex, int i)
{
	const int	*pipe = pipex->pipe_fd;
	int *const	file = pipex->file_fd;

	create_child_process_by_fork_func(pipex, i);
	if (pipex->pid[i] == 0)
	{
		close_unused_file_descriptor(pipex, pipe[i]);
		open_file(pipex, i);
		duplicate_to_standard_in_out(pipex, pipe[READ], file[WRITE]);
		execute_command(pipex, pipex->argv[3]);
		close_unused_file_descriptor(pipex, file[i]);
		exit_successfully_child_process(pipex);
	}
	close_both_pipe(pipex);
	wait_pid_for_child_process(pipex, i);
}

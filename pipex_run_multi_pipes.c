/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_multi_pipes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/04 22:35:26 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	run_child_to_pipe(\
				t_pipex *pipex, int *pipe, int *pipe_n_fd, int num);
static void	pass_pipe_next(int *pipe, int *pipe_n_fd);

size_t	run_multiple_pipes(t_pipex *pipex, int argc)
{
	size_t	add_pipes;
	int		pipe_n[2];
	size_t	num_of_pipes;

	num_of_pipes = (size_t)argc - REQUIRED_NUM;
	add_pipes = 0;
	while (add_pipes < num_of_pipes)
	{
		create_pipe_fd(pipe_n, &pipex->v_argv);
		run_child_to_pipe(pipex, pipex->pipe_fd, pipe_n, add_pipes);
		add_pipes++;
	}
	return (add_pipes);
}

static void	run_child_to_pipe(\
				t_pipex *pipex, int *pipe, int *pipe_n_fd, int add_pipes)
{
	char *const	*argv = pipex->argv;
	t_v_argv	*v_argv;
	pid_t		process_id;

	v_argv = &pipex->v_argv;
	process_id = create_child_process_by_fork_func(pipex);
	if (process_id == CHILD_PROCESS)
	{
		close_unused_file_descriptor(v_argv, pipe[WRITE]);
		close_unused_file_descriptor(v_argv, pipe_n_fd[READ]);
		duplicate_and_execute(\
			pipex, pipe[READ], pipe_n_fd[WRITE], \
				argv[add_pipes + LAST_COMMAND]);
		exit_successfully(v_argv);
	}
	close_both_pipe(v_argv, pipe);
	pass_pipe_next(pipex->pipe_fd, pipe_n_fd);
	wait_pid_for_child_process(v_argv, process_id);
}

static void	pass_pipe_next(int *pipe, int *pipe_n_fd)
{
	pipe[READ] = pipe_n_fd[READ];
	pipe[WRITE] = pipe_n_fd[WRITE];
}

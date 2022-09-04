/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/04 11:55:18 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	begin_pipex(t_pipex *pipex, int argc, char **argv, char **env);
static void	create_pipe_fd(int *pipe_fd, t_v_argv *v_argv);

static void	run_child_to_file(t_pipex *pipex, char **argv, int read_or_write, int argv_idx)
{
	const int *const pipe =  pipex->pipe_fd;;
	int *const	file_fd = pipex->file_fd;
	t_v_argv	*v_argv;
	pid_t		process_id;

	v_argv = &pipex->v_argv;
	process_id = create_child_process_by_fork_func(pipex);
	if (process_id == 0)
	{
		close_unused_file_descriptor(v_argv, pipe[read_or_write]);
		open_files_on_purpose(pipex, argv, file_fd, read_or_write);
		//open_files_on_purpose(v_argv, argv, file_fd, read_or_write);
		if (read_or_write == READ)
			duplicate_and_execute(pipex, file_fd[READ], pipe[WRITE], argv[argv_idx]);
		else if (read_or_write == WRITE)
			duplicate_and_execute(pipex, pipe[READ], file_fd[WRITE], argv[argv_idx]);
		close_unused_file_descriptor(v_argv, file_fd[read_or_write]);
		exit_successfully(v_argv);
	}
	if (read_or_write == WRITE)
		close_both_pipe(v_argv, pipe);
	wait_pid_for_child_process(v_argv, process_id);
}


static void	run_child_to_pipe(t_pipex *pipex, char **argv, int *pipe, int *pipe_n_fd, int num)
{
	t_v_argv	*v_argv;
	pid_t		process_id;

	v_argv = &pipex->v_argv;
	//pipex->pipe_n = pipex->argc - 1;
	process_id = create_child_process_by_fork_func(pipex);
	if (process_id == 0)
	{
		close_unused_file_descriptor(v_argv, pipe[WRITE]);
		close_unused_file_descriptor(v_argv, pipe_n_fd[READ]);
		//open_files_on_purpose(v_argv, argv, file_fd, read_or_write);
		duplicate_and_execute(pipex, pipe[READ], pipe_n_fd[WRITE], argv[num + 3]);
		exit_successfully(v_argv);
	}
	close_both_pipe(v_argv, pipe);
	pipex->pipe_fd[0] = pipe_n_fd[0];
	pipex->pipe_fd[1] = pipe_n_fd[1];
	//close_both_pipe(v_argv, pipe_n);
	wait_pid_for_child_process(v_argv, process_id);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	size_t	i;
	int 	pipe_n[2];

	begin_pipex(&pipex, argc, argv, env);
	create_pipe_fd(pipex.pipe_fd, &pipex.v_argv);
	run_child_to_file(&pipex, argv, READ, 2);
	i = 0;
	while (i < (size_t)argc - 5)
	{
		printf("aaaa\n");
		create_pipe_fd(pipe_n, &pipex.v_argv);
		run_child_to_pipe(&pipex, argv, pipex.pipe_fd, pipe_n, i);
		//pipex.pipe_fd[0] = pipe_n[0];
		//pipex.pipe_fd[1] = pipe_n[1];
		printf("bbbb\n");
		i++;
	}
	printf("cccc\n");
	run_child_to_file(&pipex, argv, WRITE, i + 3);
	printf("dddd\n");
	return (0);
}

static void	begin_pipex(t_pipex *pipex, int argc, char **argv, char **env)
{
	//validate_number_of_arguments(argc);
	init_struct(pipex, argc, argv, env);
}

static void	create_pipe_fd(int *pipe_fd, t_v_argv *v_argv)
{
	int	ret;

	ret = pipe(pipe_fd);
	if (ret == -1)
		exit_with_error(v_argv, "pipe()");
}

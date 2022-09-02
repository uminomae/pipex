/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/02 23:50:17 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	begin_pipex(t_pipex *pipex, int argc, char **argv, char **env);
//static void	create_pipe_fd(t_pipex *pipex);
static void	create_pipe_fd(int pipe_fd[], t_v_argv *v_argv);
static void	run_read_side(t_pipex *pipex, int i);
static void	run_write_side(t_pipex *pipex, int i);

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	begin_pipex(&pipex, argc, argv, env);
	create_pipe_fd(pipex.pipe_fd, &pipex.v_argv);
	//create_pipe_fd(&pipex);
	run_read_side(&pipex, READ);
	run_write_side(&pipex, WRITE);
	return (0);
}

static void	begin_pipex(t_pipex *pipex, int argc, char **argv, char **env)
{
	validate_number_of_arguments(argc);
	init_struct(pipex, argv, env);
}

static void	create_pipe_fd(int pipe_fd[], t_v_argv *v_argv)
//static void	create_pipe_fd(t_pipex *pipex)
{
	int	ret;

	ret = pipe(pipe_fd);
	//ret = pipe(pipex->pipe_fd);
	if (ret == -1)
		exit_with_error(v_argv, "pipe()");
		//exit_with_error(&pipex->v_argv, "pipe()");
}

static void	run_read_side(t_pipex *pipex, int i)
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
		exit_successfully(&pipex->v_argv);
	}
	wait_pid_for_child_process(pipex, i);
}

static void	run_write_side(t_pipex *pipex, int i)
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
		exit_successfully(&pipex->v_argv);
	}
	close_both_pipe(pipex);
	wait_pid_for_child_process(pipex, i);
}

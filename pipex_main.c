/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/03 02:00:51 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	begin_pipex(t_pipex *pipex, int argc, char **argv, char **env);
static void	create_pipe_fd(int *pipe_fd, t_v_argv *v_argv);
static void	run_read_side(t_pipex *pipex, int i);
static void	run_write_side(t_pipex *pipex, int i);

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	begin_pipex(&pipex, argc, argv, env);
	create_pipe_fd(pipex.pipe_fd, &pipex.v_argv);
	run_read_side(&pipex, READ);
	run_write_side(&pipex, WRITE);
	return (0);
}

static void	begin_pipex(t_pipex *pipex, int argc, char **argv, char **env)
{
	validate_number_of_arguments(argc);
	init_struct(pipex, argv, env);
}

static void	create_pipe_fd(int *pipe_fd, t_v_argv *v_argv)
{
	int	ret;

	ret = pipe(pipe_fd);
	if (ret == -1)
		exit_with_error(v_argv, "pipe()");
}

static void	run_read_side(t_pipex *pipex, int i)
{
	char *const	*argv = (char *const *)pipex->argv;
	const int	*pipe = pipex->pipe_fd;
	int *const	file_fd = pipex->file_fd;
	pid_t		process_id;

	process_id = create_child_process_by_fork_func(pipex);
	if (process_id == 0)
	{
		close_unused_file_descriptor(&pipex->v_argv, pipe[i]);
		open_files_on_purpose(&pipex->v_argv, argv, file_fd, i);
		duplicate_to_standard_in_out(pipex, file_fd[READ], pipe[WRITE]);
		execute_command(pipex, argv[2]);
		close_unused_file_descriptor(&pipex->v_argv, file_fd[i]);
		exit_successfully(&pipex->v_argv);
	}
	wait_pid_for_child_process(&pipex->v_argv, process_id);
}

static void	run_write_side(t_pipex *pipex, int i)
{
	const int	*pipe = pipex->pipe_fd;
	int *const	file = pipex->file_fd;
	pid_t	process_id;

	process_id = create_child_process_by_fork_func(pipex);
	if (process_id == 0)
	{
		close_unused_file_descriptor(&pipex->v_argv, pipe[i]);
		open_files_on_purpose(&pipex->v_argv, pipex->argv, file, i);
		duplicate_to_standard_in_out(pipex, pipe[READ], file[WRITE]);
		execute_command(pipex, pipex->argv[3]);
		close_unused_file_descriptor(&pipex->v_argv, file[i]);
		exit_successfully(&pipex->v_argv);
	}
	close_both_pipe(&pipex->v_argv, pipex->pipe_fd);
	wait_pid_for_child_process(&pipex->v_argv, process_id);	
}

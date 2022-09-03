/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/03 23:22:14 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	begin_pipex(t_pipex *pipex, int argc, char **argv, char **env);
static void	create_pipe_fd(int *pipe_fd, t_v_argv *v_argv);
static void	run_child(t_pipex *pipex, int in_out);

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	begin_pipex(&pipex, argc, argv, env);
	create_pipe_fd(pipex.pipe_fd, &pipex.v_argv);
	run_child(&pipex, READ);
	run_child(&pipex, WRITE);
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

// TODO in_outでなく、ファイルを読む側かファルに書く側か
static void	run_child(t_pipex *pipex, int in_out)
{
	char *const	*argv = (char *const *)pipex->argv;
	const int	*pipe = pipex->pipe_fd;
	int *const	file_fd = pipex->file_fd;
	pid_t		process_id;

	process_id = create_child_process_by_fork_func(pipex);
	if (process_id == 0)
	{
		close_unused_file_descriptor(&pipex->v_argv, pipe[in_out]);
		open_files_on_purpose(&pipex->v_argv, argv, file_fd, in_out);
		if (in_out == READ)
			duplicate_and_execute(pipex, file_fd[READ], pipe[WRITE],  argv[2]);
		else if (in_out == WRITE)
			duplicate_and_execute(pipex, pipe[READ], file_fd[WRITE],  argv[3]);
		close_unused_file_descriptor(&pipex->v_argv, file_fd[in_out]);
		exit_successfully(&pipex->v_argv);
	}
	if (in_out == WRITE)
		close_both_pipe(&pipex->v_argv, pipex->pipe_fd);
	wait_pid_for_child_process(&pipex->v_argv, process_id);
}

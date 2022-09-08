/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/08 16:47:56 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	duplicate_to_standard_in_out(\
			t_v_argv *v_argv, int fd_for_read, int fd_for_write);
			
pid_t	run_child_to_file(\
				t_pipex *pipex, char **argv, int read_or_write, int argv_idx)
{
	int *const	file_fd = pipex->file_fd;
	t_v_argv	*v_argv;
	pid_t		process_id;
	
	v_argv = &pipex->v_argv;
	process_id = x_fork(pipex);
	if (process_id == CHILD_PROCESS)
	{
		if (read_or_write == READ)
		{
			x_dup2(v_argv, file_fd[READ], STDIN_FILENO);
			x_dup2(v_argv, pipex->pipe_list.head->pipe_fd[WRITE], STDOUT_FILENO);
			close_both_pipe(v_argv, pipex->pipe_list.head->pipe_fd);
		}
		else if (read_or_write == WRITE)
		{
			x_dup2(v_argv, pipex->pipe_list.tail->pipe_fd[READ], STDIN_FILENO);
			x_dup2(v_argv, file_fd[WRITE], STDOUT_FILENO);
			close_both_pipe(v_argv, pipex->pipe_list.tail->pipe_fd);
		}
		get_path_from_env_and_make_list(pipex, v_argv);
		v_argv->virtual_argv = make_virtual_argv(pipex, v_argv, argv[argv_idx]);
		x_execve(pipex, v_argv->virtual_argv);
	}
	return (process_id);
}

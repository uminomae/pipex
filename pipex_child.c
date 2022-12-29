/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/12/29 02:52:18 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	dup_write_side_std_out(t_pipex *pipex, int fd[2]);
static void	dup_read_side_std_in(t_pipex *pipex, int fd[2]);
static void	build_path_and_exe(t_pipex *pipex, size_t idx);
static void	get_process_id_to_list(t_pipex *pipex, pid_t process_id, size_t i);

void	run_child_recursive(t_pipex *pipex, size_t i)
{
	int		pipe_fd[2];
	pid_t	process_id;
	size_t	num_cmd;

	process_id = 0;
	num_cmd = pipex->argc - pipex->other_cmd;
	if (i == num_cmd - 1)
		build_path_and_exe(pipex, pipex->first_cmd_idx);
	else
	{
		x_pipe(pipex, pipe_fd);
		process_id = x_fork(pipex);
		if (process_id == CHILD_PROCESS)
		{
			dup_write_side_std_out(pipex, pipe_fd);
			run_child_recursive(pipex, i + 1);
		}
		else
		{
			dup_read_side_std_in(pipex, pipe_fd);
			build_path_and_exe(pipex, pipex->argc - 2 - i);
		}
	}
	get_process_id_to_list(pipex, process_id, i);
}

static void	dup_write_side_std_out(t_pipex *pipex, int fd[2])
{
	x_close(pipex, fd[READ]);
	x_dup2(pipex, fd[WRITE], STDOUT_FILENO);
	x_close(pipex, fd[WRITE]);
}

static void	dup_read_side_std_in(t_pipex *pipex, int fd[2])
{
	x_close(pipex, fd[WRITE]);
	x_dup2(pipex, fd[READ], READ);
	x_close(pipex, fd[READ]);
}

static void	build_path_and_exe(t_pipex *pipex, size_t idx)
{
	get_path(pipex, &pipex->v_argv);
	pipex->v_argv.virtual_argv = \
		make_virtual_argv(pipex, &pipex->v_argv, pipex->argv[idx]);
	x_execve(pipex, pipex->v_argv.virtual_argv);
}

static void	get_process_id_to_list(t_pipex *pipex, pid_t process_id, size_t i)
{
	t_pid_node	*node;
	size_t		j;

	j = 0;
	node = pipex->pid_list.head;
	while (j < i + 1)
	{
		node->process_id = process_id;
		node = node->next;
		j++;
	}
}

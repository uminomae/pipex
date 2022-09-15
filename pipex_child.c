/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/15 19:03:54 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void		run_child_to_file_read(t_pipex *pipex);
static void		run_child_to_file_write(t_pipex *pipex);
static pid_t	run_child_to_file(\
				t_pipex *pipex, char **argv, int read_or_write, int argv_idx);

static void	dup_child_std_in_out(t_pipex *pipex, int pipe_fd[2])
{
	x_close(pipex, pipe_fd[READ]);
	x_dup2(pipex, pipe_fd[WRITE], STDOUT_FILENO);
	x_close(pipex, pipe_fd[WRITE]);
}

static void	dup_parent_std_in_out(t_pipex *pipex, int pipe_fd[2])
{
	x_close(pipex, pipe_fd[WRITE]);
	x_dup2(pipex, pipe_fd[READ], READ);
	x_close(pipex, pipe_fd[READ]);
}

void	build_cmd_path_and_exe(t_pipex *pipex, size_t idx)
{
	get_path(pipex, &pipex->v_argv);
	pipex->v_argv.virtual_argv = \
		make_virtual_argv(pipex, &pipex->v_argv, pipex->argv[idx]);
	x_execve(pipex, pipex->v_argv.virtual_argv);
}

void	get_process_id_to_list(t_pipex *pipex, pid_t process_id, size_t i)
{
	t_pid_node	*node;
	size_t j;

	j = 0;
	node = pipex->pid_list.head;
	while (j < i + 1)
	{
		node->process_id = process_id;
		node = node->next;
		j++;
	}
}

void	run_child_recursive(t_pipex *pipex, size_t i)
{
	int	pipe_fd[2];
	pid_t	process_id;

	process_id = 0;
	size_t	num_cmd = pipex->argc - pipex->other_cmd;
	if (i == num_cmd - 1)
		build_cmd_path_and_exe(pipex, pipex->first_cmd_idx);
	else
	{
		x_pipe(pipex, pipe_fd);
		process_id = x_fork(pipex);
		if (process_id == CHILD_PROCESS)
		{
			dup_child_std_in_out(pipex, pipe_fd);
			run_child_recursive(pipex, i + 1);
		}
		else
		{
			dup_parent_std_in_out(pipex, pipe_fd);
			build_cmd_path_and_exe(pipex, pipex->argc - 2 - i);
		}
	}
	get_process_id_to_list(pipex, process_id, i);
}

void	run_separate_child2(t_pipex *pipex)
{
	run_child_recursive(pipex, 0);
}

void	run_separate_child(t_pipex *pipex, char **argv, size_t num_pipe)
{
	size_t				add_pipe;
	t_pid_node *const	head = pipex->pid_list.head;
	t_pid_node *const	tail = pipex->pid_list.tail;
	int					last_cmd_idx;

	head->process_id = \
		run_child_to_file(pipex, argv, READ, pipex->first_cmd_idx);
	add_pipe = run_multiple_pipes(pipex, num_pipe);
	last_cmd_idx = add_pipe + pipex->last_cmd_idx;
	tail->process_id = run_child_to_file(pipex, argv, WRITE, last_cmd_idx);
}

static pid_t	run_child_to_file(\
			t_pipex *pipex, char **argv, int read_or_write, int argv_idx)
{
	pid_t	process_id;

	process_id = x_fork(pipex);
	if (process_id == CHILD_PROCESS)
	{
		if (read_or_write == READ)
			run_child_to_file_read(pipex);
		else if (read_or_write == WRITE)
			run_child_to_file_write(pipex);
		get_path(pipex, &pipex->v_argv);
		pipex->v_argv.virtual_argv = \
			make_virtual_argv(pipex, &pipex->v_argv, argv[argv_idx]);
		x_execve(pipex, pipex->v_argv.virtual_argv);
	}
	return (process_id);
}

static void	run_child_to_file_read(t_pipex *pipex)
{
	x_dup2(pipex, pipex->file_fd[READ], STDIN_FILENO);
	x_dup2(pipex, pipex->pipe_list.head->pipe_fd[WRITE], STDOUT_FILENO);
	close_both_fd(pipex, pipex->pipe_list.head->pipe_fd);
}

static void	run_child_to_file_write(t_pipex *pipex)
{
	x_dup2(pipex, pipex->pipe_list.tail->pipe_fd[READ], STDIN_FILENO);
	x_dup2(pipex, pipex->file_fd[WRITE], STDOUT_FILENO);
	close_both_fd(pipex, pipex->pipe_list.tail->pipe_fd);
}

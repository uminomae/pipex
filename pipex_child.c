/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/14 14:16:46 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void		run_child_to_file_read(t_pipex *pipex);
static void		run_child_to_file_write(t_pipex *pipex);
static pid_t	run_child_to_file(\
				t_pipex *pipex, char **argv, int read_or_write, int argv_idx);

void	run_separate_child(t_pipex *pipex, char **argv, size_t num_pipe)
{
	size_t				add_pipe;
	t_pid_node *const	head = pipex->pid_list.head;
	t_pid_node *const	tail = pipex->pid_list.tail;
	int					last_cmd_idx;

	head->process_id = run_child_to_file(\
			pipex, argv, READ, pipex->first_cmd_idx);
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

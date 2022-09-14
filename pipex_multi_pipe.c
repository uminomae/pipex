/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_multi_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/14 12:43:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	run_child_multi(\
				t_pipex *pipex, int *pipe, int *pipe_n_fd, int add_pipe);

size_t	run_multiple_pipes(t_pipex *pipex, size_t num_pipe)
{
	size_t		i;
	t_pipe_node	*node;
	t_pid_node	*node_pid;

	if (num_pipe == 1)
		return (0);
	// node = pipex->pipe_list.tail;
	// node_pid = pipex->pid_list.tail->prev;
	node = pipex->pipe_list.head->next;
	node_pid = pipex->pid_list.head->next;
	i = 0;
	while (node != NULL)
	{
		node_pid->process_id = run_child_multi(\
			pipex, node->prev->pipe_fd, node->pipe_fd, i);
		// node = node->prev;
		// node_pid = node_pid->prev;
		node = node->next;
		node_pid = node_pid->next;
		i++;
	}
	return (i);
}

static pid_t	run_child_multi(\
				t_pipex *pipex, int *prev_pipe, int *pipe, int add_pipe)
{
	char *const	*argv = pipex->argv;
	t_arg		*v_argv;
	pid_t		process_id;

	v_argv = &pipex->v_argv;
	process_id = x_fork(pipex);
	if (process_id == CHILD_PROCESS)
	{
		x_dup2(pipex, prev_pipe[READ], STDIN_FILENO);
		x_dup2(pipex, pipe[WRITE], STDOUT_FILENO);
		close_both_fd(pipex, prev_pipe);
		close_both_fd(pipex, pipe);
		get_path(pipex, v_argv);
		// v_argv->virtual_argv = make_virtual_argv(
		// 	pipex, v_argv, argv[pipex->argc - 1 - add_pipe - 2]);
		v_argv->virtual_argv = make_virtual_argv(
			pipex, v_argv, argv[add_pipe + pipex->last_cmd_idx]);
		x_execve(pipex, v_argv->virtual_argv);
	}
	x_close(pipex, prev_pipe[WRITE]);
	// x_close(pipex, prev_pipe[READ]);
	return (process_id);
}

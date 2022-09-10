/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_multi_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/10 13:37:23 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	run_child_multi(\
				t_pipex *pipex, int *pipe, int *pipe_n_fd, int add_pipe);

size_t	run_multiple_pipes(t_pipex *pipex, size_t num_pipe)
{
	size_t		i;
	t_pipe_node	*node;

	if (num_pipe == 1)
		return (0);
	node = pipex->pipe_list.head->next;
	i = 0;
	while (node != NULL)
	{
		node->process_id = run_child_multi(\
				pipex, node->prev->pipe_fd, node->pipe_fd, i);
		node = node->next;
		i++;
	}
	return (i);
}

static pid_t	run_child_multi(\
				t_pipex *pipex, int *prev_pipe, int *pipe, int add_pipe)
{
	char *const	*argv = pipex->argv;
	t_arg	*v_argv;
	pid_t		process_id;

	v_argv = &pipex->v_argv;
	process_id = x_fork(pipex);
	if (process_id == CHILD_PROCESS)
	{
		x_dup2(v_argv, prev_pipe[READ], STDIN_FILENO);
		x_dup2(v_argv, pipe[WRITE], STDOUT_FILENO);
		close_both_fd(v_argv, prev_pipe);
		close_both_fd(v_argv, pipe);
		get_path(pipex, v_argv);
		v_argv->virtual_argv = make_virtual_argv(\
				pipex, v_argv, argv[add_pipe + LAST_COMMAND]);
		x_execve(pipex, v_argv->virtual_argv);
	}
	x_close(v_argv, prev_pipe[WRITE]);
	return (process_id);
}

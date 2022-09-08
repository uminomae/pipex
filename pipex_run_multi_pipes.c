/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_multi_pipes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/08 15:39:27 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//static void	run_child_to_pipe(\
//				t_pipex *pipex, int *pipe, int *pipe_n_fd, int num);
pid_t	run_child_to_pipe(\
				t_pipex *pipex, int *pipe, int *pipe_n_fd, int add_pipe);

//void	run_multiple_pipes(t_pipex *pipex, size_t add_pipe)
size_t	run_multiple_pipes(t_pipex *pipex, size_t num_pipe)
{
	size_t	i;
	t_pipe_node *node;

	if (num_pipe == 1)
		return (0);
	node = pipex->pipe_list.head->next;
	i = 0;
	while (node != NULL)
	{
		node->process_id = run_child_to_pipe(pipex, node->prev->pipe_fd, node->pipe_fd, num_pipe + i);
		node = node->next;
		i++;
	}
	return (i);
}

pid_t	run_child_to_pipe(\
				t_pipex *pipex, int *prev_pipe, int *pipe, int add_pipe)
{
	char *const	*argv = pipex->argv;
	t_v_argv	*v_argv;
	pid_t		process_id;

	v_argv = &pipex->v_argv;
	process_id = create_child_process_by_fork_func(pipex);

	if (process_id == CHILD_PROCESS)
	{
		x_dup2(v_argv, prev_pipe[READ], STDIN_FILENO);
		x_dup2(v_argv, pipe[WRITE], STDOUT_FILENO);
		close_both_pipe(v_argv, prev_pipe);
		close_both_pipe(v_argv, pipe);
		get_virtual_argv(pipex, argv[add_pipe + LAST_COMMAND]);
	}
	//x_close(v_argv, prev_pipe[WRITE]);
	//x_close(v_argv, prev_pipe[READ]);
	//x_close(v_argv, pipe[READ]);
	//x_close(v_argv, pipe[WRITE]);
	return (process_id);
}

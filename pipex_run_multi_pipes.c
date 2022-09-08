/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_multi_pipes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/08 14:44:19 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//static void	run_child_to_pipe(\
//				t_pipex *pipex, int *pipe, int *pipe_n_fd, int num);
pid_t	run_child_to_pipe(\
				t_pipex *pipex, int *pipe, int *pipe_n_fd, int add_pipes);

size_t	run_multiple_pipes(t_pipex *pipex, int argc, size_t add_pipe)
{
	size_t	i;
	t_pipe_node *node;

	(void)argc;
	(void)add_pipe;
	//if (pipex->pipe_list.head != NULL)
	node = pipex->pipe_list.head->next;
	i = 1;
	while (node != NULL)
	{
		//i++;
		node->process_id = run_child_to_pipe(pipex, node->prev->pipe_fd, node->pipe_fd, i);
		node = node->next;
		i++;
	}
	return (i);
}

pid_t	run_child_to_pipe(\
				t_pipex *pipex, int *prev_pipe, int *pipe, int add_pipes)
{
	char *const	*argv = pipex->argv;
	t_v_argv	*v_argv;
	pid_t		process_id;

	v_argv = &pipex->v_argv;
	process_id = create_child_process_by_fork_func(pipex);

	if (process_id == CHILD_PROCESS)
	{
		x_close(v_argv, prev_pipe[WRITE]);
		x_close(v_argv, pipe[READ]);
		duplicate_and_execute(\
			pipex, prev_pipe[READ], pipe[WRITE], \
				argv[add_pipes + LAST_COMMAND]);
			//pipex, prev_pipe[READ], pipe[WRITE], \
			//	argv[add_pipes + LAST_COMMAND]);
	}
	x_close(v_argv, prev_pipe[WRITE]);
	x_close(v_argv, prev_pipe[READ]);
	//x_close(v_argv, pipe[READ]);
	//x_close(v_argv, pipe[WRITE]);
	return (process_id);
}

//static void	duplicate_to_standard_in_out(\
//			t_v_argv *v_argv, int fd_for_read, int fd_for_write)
//{
//	x_dup2(v_argv, fd_for_read, STDIN_FILENO);
//	x_dup2(v_argv, fd_for_write, STDOUT_FILENO);
//}
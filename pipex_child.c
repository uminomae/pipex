/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/09 10:37:41 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	run_child_to_file(\
				t_pipex *pipex, char **argv, int read_or_write, int argv_idx);
static size_t	run_multiple_pipes(t_pipex *pipex, size_t num_pipe);
static pid_t	run_child_to_pipe(\
				t_pipex *pipex, int *pipe, int *pipe_n_fd, int add_pipe);

void	run_child(t_pipex *pipex, char **argv, size_t num_pipe)
{
	size_t	add_pipe;

	pipex->pipe_list.head->process_id = \
		run_child_to_file(pipex, argv, READ, FIRST_CMD);
	add_pipe = run_multiple_pipes(pipex, num_pipe);
	pipex->pipe_list.tail->process_id = \
		run_child_to_file(pipex, argv, WRITE, add_pipe + LAST_COMMAND);
}

static size_t	run_multiple_pipes(t_pipex *pipex, size_t num_pipe)
{
	size_t		i;
	t_pipe_node	*node;

	if (num_pipe == 1)
		return (0);
	node = pipex->pipe_list.head->next;
	i = 0;
	while (node != NULL)
	{
		node->process_id = run_child_to_pipe(\
				pipex, node->prev->pipe_fd, node->pipe_fd, i);
		node = node->next;
		i++;
	}
	return (i);
}

static void	run_child_to_file_read(t_pipex *pipex)
{
	x_dup2(&pipex->v_argv, pipex->file_fd[READ], STDIN_FILENO);
	x_dup2(&pipex->v_argv, \
		pipex->pipe_list.head->pipe_fd[WRITE], STDOUT_FILENO);
	close_both_fd(&pipex->v_argv, pipex->pipe_list.head->pipe_fd);
}

static void	run_child_to_file_write(t_pipex *pipex)
{
	x_dup2(&pipex->v_argv, \
				pipex->pipe_list.tail->pipe_fd[READ], STDIN_FILENO);
	x_dup2(&pipex->v_argv, pipex->file_fd[WRITE], STDOUT_FILENO);
	close_both_fd(&pipex->v_argv, pipex->pipe_list.tail->pipe_fd);
}

static pid_t	run_child_to_file(\
				t_pipex *pipex, char **argv, int read_or_write, int argv_idx)
{
	pid_t		process_id;

	process_id = x_fork(pipex);
	if (process_id == CHILD_PROCESS)
	{
		if (read_or_write == READ)
			run_child_to_file_read(pipex);
		else if (read_or_write == WRITE)
			run_child_to_file_write(pipex);
		get_path_from_env_and_make_list(pipex, &pipex->v_argv);
		pipex->v_argv.virtual_argv = \
			make_virtual_argv(pipex, &pipex->v_argv, argv[argv_idx]);
		x_execve(pipex, pipex->v_argv.virtual_argv);
	}
	return (process_id);
}


static pid_t	run_child_to_pipe(\
				t_pipex *pipex, int *prev_pipe, int *pipe, int add_pipe)
{
	char *const	*argv = pipex->argv;
	t_v_argv	*v_argv;
	pid_t		process_id;

	v_argv = &pipex->v_argv;
	process_id = x_fork(pipex);
	if (process_id == CHILD_PROCESS)
	{
		x_dup2(v_argv, prev_pipe[READ], STDIN_FILENO);
		x_dup2(v_argv, pipe[WRITE], STDOUT_FILENO);
		close_both_fd(v_argv, prev_pipe);
		close_both_fd(v_argv, pipe);

		get_path_from_env_and_make_list(pipex, v_argv);

		v_argv->virtual_argv = make_virtual_argv(\
				pipex, v_argv, argv[add_pipe + LAST_COMMAND]);

		x_execve(pipex, v_argv->virtual_argv);
	}

	x_close(v_argv, prev_pipe[WRITE]);
	
	return (process_id);
}

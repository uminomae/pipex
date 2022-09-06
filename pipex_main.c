/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/07 06:50:33 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(\
			t_pipex *pipex, char *const *argv, int *file_fd);
			
void	x_pipe(int pipe_fd[2], t_v_argv *v_argv)
{
	int	ret;

	ret = pipe(pipe_fd);
	if (ret == ERR_NUM)
		exit_with_error(v_argv, ERR_MSG_PIPE);
}

t_pipe_node	*init_node(t_v_argv *v_argv)
{
	t_pipe_node *node;

	node = (t_pipe_node *)malloc_and_check_for_null(v_argv, sizeof(t_pipe_node));
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_pipe_to_node(t_pipex *pipex, int pipe_fd[2])
{
	t_pipe_node *node;

	node = init_node(&pipex->v_argv);
	node->pipe_fd[0] = pipe_fd[0];
	node->pipe_fd[1] = pipe_fd[1];
	if (pipex->pipe_list.head == NULL)
	{
		pipex->pipe_list.head = node;
		pipex->pipe_list.tail = node;
	}
	else if (pipex->pipe_list.head->next == NULL)
	{
		pipex->pipe_list.head->next = node;
		pipex->pipe_list.head->next->prev = pipex->pipe_list.head;
		pipex->pipe_list.tail = node;
	}
	else
	{
		pipex->pipe_list.tail->next = node;
		pipex->pipe_list.tail->next->prev = pipex->pipe_list.tail;
		pipex->pipe_list.tail = node;
	}

}

size_t	make_pipe(t_pipex *pipex, int argc, size_t argc_of_base)
{
	int		add_pipe[2];
	size_t	i;
	size_t	num_to_make;
	t_pipe_node *node;

	num_to_make = 1;
	num_to_make += (size_t)argc - argc_of_base;
	i = 0;
	while (i < num_to_make)
	{
		x_pipe(add_pipe, &pipex->v_argv);
		add_pipe_to_node(pipex, add_pipe);
		node = pipex->pipe_list.head->next;
		while (node != NULL)
		{
			node->pipe_fd[READ] = node->prev->pipe_fd[WRITE];
			//if (node->next != NULL)
			//	node->pipe_fd[WRITE] = node->next->pipe_fd[READ];
			node = node->next;
		}
		i++;
	}
	return (i);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex				pipex;
	size_t				num_pipe;
	t_pipe_node 		*node;

	begin_pipex(&pipex, argc, argv, env);
	open_files(&pipex, argv, pipex.file_fd);
	num_pipe = make_pipe(&pipex, argc, NUM_OF_BASE);
	
	pipex.pipe_list.head->process_id = run_child_to_file(&pipex, argv, READ, FIRST_CMD);
	run_multiple_pipes(&pipex, argc, num_pipe - 1);
	pipex.pipe_list.tail->process_id = run_child_to_file(&pipex, argv, WRITE, num_pipe - 1 + LAST_COMMAND);
	
	close_unused_file_descriptor(&pipex.v_argv, pipex.file_fd[READ]);
	close_unused_file_descriptor(&pipex.v_argv, pipex.file_fd[WRITE]);
	node = pipex.pipe_list.head;
	while (node != NULL)
	{
		close_unused_file_descriptor(&pipex.v_argv, node->pipe_fd[READ]);
		close_unused_file_descriptor(&pipex.v_argv, node->pipe_fd[WRITE]);
		//close_both_pipe(&pipex.v_argv, node->pipe_fd);
		node = node->next;
	}
	node = pipex.pipe_list.head;
	while (node != NULL)
	{
		wait_pid_for_child_process(&pipex.v_argv, node->process_id);
		node = node->next;
	}
	return (0);
}

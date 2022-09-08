/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/08 16:44:52 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
			
t_pipe_node	*init_pipe_node(t_v_argv *v_argv)
{
	t_pipe_node *node;

	node = (t_pipe_node *)x_malloc(v_argv, sizeof(t_pipe_node));
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_pipe_to_node(t_pipex *pipex, int pipe_fd[2])
{
	t_pipe_node *node;

	node = init_pipe_node(&pipex->v_argv);
	node->pipe_fd[0] = pipe_fd[0];
	node->pipe_fd[1] = pipe_fd[1];
	if (pipex->pipe_list.head == NULL)
	{
		pipex->pipe_list.head = node;
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
			//node->pipe_fd[READ] = node->prev->pipe_fd[WRITE];
			//if (node->next != NULL)
			//	node->pipe_fd[WRITE] = node->next->pipe_fd[READ];
			node = node->next;
		}
		i++;
	}
	return (i);
}

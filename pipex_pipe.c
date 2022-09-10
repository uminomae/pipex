/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/10 13:56:09 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pipe_node	*init_pipe_node(t_arg *v_argv);
static void			add_pipe_to_node(t_pipex *pipex, int pipe_fd[2]);

size_t	make_pipe(t_pipex *pipex, int argc, size_t argc_of_base)
{
	int		add_pipe[2];
	size_t	i;
	size_t	num_to_make;

	num_to_make = (size_t)argc - argc_of_base + 1;
	i = 0;
	while (i < num_to_make)
	{
		x_pipe(add_pipe, &pipex->v_argv);
		add_pipe_to_node(pipex, add_pipe);
		i++;
	}
	return (i);
}

static t_pipe_node	*init_pipe_node(t_arg *v_argv)
{
	t_pipe_node	*node;

	node = (t_pipe_node *)x_malloc(v_argv, sizeof(t_pipe_node));
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

static void	add_pipe_to_node(t_pipex *pipex, int pipe_fd[2])
{
	t_pipe_node	*node;

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


static t_pid_node	*init_pid_node(t_arg *v_argv)
{
	t_pid_node	*node;

	node = (t_pid_node *)x_malloc(v_argv, sizeof(t_pid_node));
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

static void	add_pid_to_node(t_pipex *pipex, int process_id)
{
	t_pid_node	*node;

	node = init_pid_node(&pipex->v_argv);
	node->process_id = process_id;
	if (pipex->pid_list.head == NULL)
	{
		pipex->pid_list.head = node;
		pipex->pid_list.tail = node;
	}
	else
	{
		pipex->pid_list.tail->next = node;
		pipex->pid_list.tail->next->prev = pipex->pid_list.tail;
		pipex->pid_list.tail = node;
	}
}

void	make_pid_struct(t_pipex *pipex, int argc, pid_t process_id)
{
	size_t	i;
	size_t	num_to_make;

	num_to_make = (size_t)argc - 3;
	i = 0;
	while (i < num_to_make)
	{
		add_pid_to_node(pipex, process_id);
		i++;
	}
	return ;
}


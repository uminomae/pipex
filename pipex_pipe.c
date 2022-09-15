/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/15 11:10:34 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pipe_node	*init_pipe_node(t_pipex *pipex);
static void			add_pipe_to_list(t_pipex *pipex);
static void			make_first_pipe_node(t_pipe_list *list, t_pipe_node *node);
static void			add_last_pipe_node(t_pipe_list *list, t_pipe_node *node);

size_t	make_pipe(t_pipex *pipex, int argc, size_t argc_normal)
{
	size_t	i;
	size_t	num_to_make;

	num_to_make = (size_t)argc - argc_normal + 1;
	i = 0;
	while (i < num_to_make)
	{
		add_pipe_to_list(pipex);
		i++;
	}
	return (i);
}

static void	add_pipe_to_list(t_pipex *pipex)
{
	t_pipe_node	*node;
	int		add_pipe[2];

	node = init_pipe_node(pipex);
	x_pipe(pipex, add_pipe);
	node->pipe_fd[0] = add_pipe[0];
	node->pipe_fd[1] = add_pipe[1];
	if (pipex->pipe_list.head == NULL)
		make_first_pipe_node(&pipex->pipe_list, node);
	else
		add_last_pipe_node(&pipex->pipe_list, node);
}

static t_pipe_node	*init_pipe_node(t_pipex *pipex)
{
	t_pipe_node	*node;

	node = (t_pipe_node *)x_malloc_and_add_list(pipex, sizeof(t_pipe_node));
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

static void	make_first_pipe_node(t_pipe_list *list, t_pipe_node *node)
{
	list->head = node;
	list->tail = node;
}

static void	add_last_pipe_node(t_pipe_list *list, t_pipe_node *node)
{
	list->tail->next = node;
	list->tail->next->prev = list->tail;
	list->tail = node;
}

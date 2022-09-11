/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/11 19:02:35 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pid_node	*init_pid_node(t_pipex *pipex);
static void			add_pid_node(t_pipex *pipex);
static void			make_first_pid_node(t_pid_list *list, t_pid_node *node);
static void			add_last_pid_node(t_pid_list *list, t_pid_node *node);

void	init_pid_list(t_pipex *pipex, int argc, size_t other_cmd)
{
	size_t	i;
	size_t	num_to_make;

	num_to_make = (size_t)argc - other_cmd;
	i = 0;
	while (i < num_to_make)
	{
		add_pid_node(pipex);
		i++;
	}
	return ;
}

static void	add_pid_node(t_pipex *pipex)
{
	t_pid_node	*node;

	node = init_pid_node(pipex);
	if (pipex->pid_list.head == NULL)
		make_first_pid_node(&pipex->pid_list, node);
	else
		add_last_pid_node(&pipex->pid_list, node);
}

static t_pid_node	*init_pid_node(t_pipex *pipex)
{
	t_pid_node	*node;

	node = (t_pid_node *)x_malloc(pipex, sizeof(t_pid_node));
	//node = (t_pid_node *)x_malloc_and_add_list(pipex, sizeof(t_pid_node));
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

static void	make_first_pid_node(t_pid_list *list, t_pid_node *node)
{
	list->head = node;
	list->tail = node;
}

static void	add_last_pid_node(t_pid_list *list, t_pid_node *node)
{
	list->tail->next = node;
	list->tail->next->prev = list->tail;
	list->tail = node;
}

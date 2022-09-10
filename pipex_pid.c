/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/10 14:54:54 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pid_node	*init_pid_node(t_pipex *pipex);
static void	add_pid_to_node(t_pipex *pipex);

void	init_pid_struct(t_pipex *pipex, int argc)
{
	size_t	i;
	size_t	num_to_make;

	num_to_make = (size_t)argc - 3;
	i = 0;
	while (i < num_to_make)
	{
		add_pid_to_node(pipex);
		i++;
	}
	return ;
}

static t_pid_node	*init_pid_node(t_pipex *pipex)
{
	t_pid_node	*node;

	node = (t_pid_node *)x_malloc(pipex, sizeof(t_pid_node));
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

static void	add_pid_to_node(t_pipex *pipex)
{
	t_pid_node	*node;

	node = init_pid_node(pipex);
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


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/16 08:16:44 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_cmd_node	*init_cmd_node(t_pipex *pipex);
static void			add_cmd_node(t_pipex *pipex);
static void			make_first_cmd_node(t_cmd_list *list, t_cmd_node *node);
static void			add_last_cmd_node(t_cmd_list *list, t_cmd_node *node);

void	init_cmd_list(t_pipex *pipex, int argc, size_t other_cmd)
{
	size_t	i;
	size_t	num_to_make;

	num_to_make = (size_t)argc - other_cmd;
	i = 0;
	while (i < num_to_make)
	{
		add_cmd_node(pipex);
		i++;
	}
	return ;
}

static void	add_cmd_node(t_pipex *pipex)
{
	t_cmd_node	*node;

	node = init_cmd_node(pipex);
	if (pipex->cmd_list.head == NULL)
		make_first_cmd_node(&pipex->cmd_list, node);
	else
		add_last_cmd_node(&pipex->cmd_list, node);
}

static t_cmd_node	*init_cmd_node(t_pipex *pipex)
{
	t_cmd_node	*node;

	node = (t_cmd_node *)x_malloc_and_add_list(pipex, sizeof(t_cmd_node));
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

static void	make_first_cmd_node(t_cmd_list *list, t_cmd_node *node)
{
	list->head = node;
	list->tail = node;
}

static void	add_last_cmd_node(t_cmd_list *list, t_cmd_node *node)
{
	list->tail->next = node;
	list->tail->next->prev = list->tail;
	list->tail = node;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_alloc_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/11 18:59:52 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_alloc_node	*init_alloc_node(void);
static void			make_first_alloc_node(\
						t_alloc_list *list, t_alloc_node *node);
static void			add_last_alloc_node(t_alloc_list *list, t_alloc_node *node);
static void			add_alloc_list(t_pipex *pipex, void *ptr);

static t_alloc_node	*init_alloc_node(void)
{
	t_alloc_node	*node;

	node = (t_alloc_node *)malloc(sizeof(t_alloc_node));
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

static void	make_first_alloc_node(t_alloc_list *list, t_alloc_node *node)
{
	list->head = node;
	list->tail = node;
}

static void	add_last_alloc_node(t_alloc_list *list, t_alloc_node *node)
{
	list->tail->next = node;
	list->tail->next->prev = list->tail;
	list->tail = node;
}

static void	add_alloc_list(t_pipex *pipex, void *ptr)
{
	t_alloc_node	*node;

	node = init_alloc_node();
	node->ptr = ptr;
	if (pipex->alloc_list.head == NULL)
		make_first_alloc_node(&pipex->alloc_list, node);
	else
		add_last_alloc_node(&pipex->alloc_list, node);
}

void	*x_malloc_and_add_list(t_pipex *pipex, size_t size)
{
	void	*ret;

	ret = malloc(sizeof(void *) * size);
	if (ret == NULL)
		exit_with_error(pipex, ERR_MSG_MALLOC, 1);
	add_alloc_list(pipex, ret);
	return (ret);
}

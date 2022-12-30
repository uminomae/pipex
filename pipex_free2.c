/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:23 by hioikawa          #+#    #+#             */
/*   Updated: 2022/12/30 19:03:50 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_alloc_list(t_alloc_list *alloc_list)
{
	t_alloc_node	*node;
	t_alloc_node	*temp;

	node = alloc_list->head;
	if (node == NULL)
		return ;
	while (node != NULL)
	{
		temp = node;
		free(node->ptr);
		node->ptr = NULL;
		node = node->next;
		free(temp);
		temp = NULL;
	}
}

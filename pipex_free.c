/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:23 by hioikawa          #+#    #+#             */
/*   Updated: 2022/12/31 01:06:49 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	safe_free(char **malloc_ptr)
{
	free(*malloc_ptr);
	*malloc_ptr = NULL;
}

static void	free_list(char **list)
{
	size_t	i;

	i = 0;
	if (list == NULL)
		return ;
	while (list[i] != NULL)
	{
		safe_free(&list[i]);
		i++;
	}
	free(list[i]);
	free(list);
	list = NULL;
}

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

void	free_struct(t_pipex *pipex)
{
	free_list(pipex->v_argv.list_abs_path_cmd);
	free_list(pipex->v_argv.temp_divided_list);
	free_list(pipex->v_argv.list_of_directory);
	free_list(pipex->v_argv.virtual_argv);
	free_alloc_list(&pipex->alloc_list);
}

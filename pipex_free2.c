/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:23 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/11 18:57:33 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pid_list(t_pid_list *pid_list)
{
	t_pid_node	*node;
	t_pid_node	*temp;

	node = pid_list->head;
	if (node == NULL)
		return ;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		free(temp);
		temp = NULL;
	}
}

void	free_pipe_list(t_pipe_list *pipe_list)
{
	t_pipe_node	*node;
	t_pipe_node	*temp;

	node = pipe_list->head;
	if (node == NULL)
		return ;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		free(temp);
		temp = NULL;
	}
}

//void	free_alloc_list(t_alloc_list *alloc_list)
//{
//	t_alloc_node	*node;
//	t_alloc_node	*temp;

//	node = alloc_list->head;
//	if (node == NULL)
//		return ;
//	while (node != NULL)
//	{
//		temp = node;
//		node->ptr = NULL;
//		node = node->next;
//		free(temp);
//		temp = NULL;
//	}
//}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:23 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/10 15:13:35 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pid_list(t_pid_list *pid_list)
{
	t_pid_node	*node;

	node = pid_list->head;
	if (node == NULL)
		return ;
	while (node != NULL)
	{
		free(node);
		node = NULL;
		node = node->next;
	}
}

void	free_pipe_list(t_pipe_list *pipe_list)
{
	t_pipe_node	*node;

	node = pipe_list->head;
	if (node == NULL)
		return ;
	while (node != NULL)
	{
		free(node);
		node = NULL;
		node = node->next;
	}
}

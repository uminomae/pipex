/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/13 04:35:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_all_child(t_pipex *pipex)
{
	t_pid_node	*node;
	size_t i=0;

	node = pipex->pid_list.head;
	while (node != NULL)
	{
		x_waitpid(pipex, node->process_id);
		node = node->next;
		i++;
		printf("i=%zu\n", i);
	}
}

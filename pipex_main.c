/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/08 14:34:46 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(\
			t_pipex *pipex, char *const *argv, int *file_fd);
size_t	make_pipe(t_pipex *pipex, int argc, size_t argc_of_base);


int	main(int argc, char **argv, char **env)
{
	t_pipex				pipex;
	size_t				num_pipe;
	t_pipe_node 		*node;

	begin_pipex(&pipex, argc, argv, env);

	open_files(&pipex, argv, pipex.file_fd);
	num_pipe = make_pipe(&pipex, argc, NUM_OF_BASE);
	
	pipex.pipe_list.head->process_id = run_child_to_file(&pipex, argv, READ, FIRST_CMD);
	run_multiple_pipes(&pipex, argc, num_pipe - 1);
	pipex.pipe_list.tail->process_id = run_child_to_file(&pipex, argv, WRITE, num_pipe - 1 + LAST_COMMAND);
	
	//close_unused_file_descriptor(&pipex.v_argv, pipex.file_fd[READ]);
	//close_unused_file_descriptor(&pipex.v_argv, pipex.file_fd[WRITE]);
	
	node = pipex.pipe_list.head;
	while (node != NULL)
	{
		//close_unused_file_descriptor(&pipex.v_argv, node->pipe_fd[READ]);
		//close_unused_file_descriptor(&pipex.v_argv, node->pipe_fd[WRITE]);
		//close_both_pipe(&pipex.v_argv, node->pipe_fd);
		node = node->next;
	}
	node = pipex.pipe_list.head;
	while (node != NULL)
	{
		wait_pid_for_child_process(&pipex.v_argv, node->process_id);
		node = node->next;
	}
	return (0);
}

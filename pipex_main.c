/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/09 08:46:57 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//extern char **environ;


//int	main(int argc, char **argv, char **env)
int	main(int argc, char **argv)
{
	t_pipex				pipex;
	size_t				num_pipe;
	size_t				add_pipe;
	t_pipe_node 		*node;

	//begin_pipex(&pipex, argc, argv, env);
	begin_pipex(&pipex, argc, argv);

	open_files(&pipex, argv, pipex.file_fd);
	num_pipe = make_pipe(&pipex, argc, NUM_OF_BASE);
	pipex.pipe_list.head->process_id = \
		run_child_to_file(&pipex, argv, READ, FIRST_CMD);
	add_pipe = run_multiple_pipes(&pipex, num_pipe);
	pipex.pipe_list.tail->process_id = \
		run_child_to_file(&pipex, argv, WRITE, add_pipe + LAST_COMMAND);
	x_close(&pipex.v_argv, pipex.file_fd[READ]);
	x_close(&pipex.v_argv, pipex.file_fd[WRITE]);
	close_both_pipe(&pipex.v_argv, pipex.pipe_list.tail->pipe_fd);
	node = pipex.pipe_list.head;
	while (node != NULL)
	{
		x_waitpid(&pipex.v_argv, node->process_id);
		node = node->next;
	}
	return (0);
}

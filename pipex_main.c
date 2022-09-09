/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/09 17:04:33 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_here_doc(t_pipex *pipex)
{
	(void)pipex;
}

int	main(int argc, char **argv)
{
	t_pipex		pipex;
	size_t		num_pipe;

	begin_pipex(&pipex, argc, argv);
	if (pipex.flag_here_doc == true)
		run_here_doc(&pipex);
	open_files(&pipex, argc, argv, pipex.file_fd);
	num_pipe = make_pipe(&pipex, argc, NUM_BASE);
	run_child(&pipex, argv, num_pipe);
	close_both_fd(&pipex.v_argv, pipex.file_fd);
	close_both_fd(&pipex.v_argv, pipex.pipe_list.tail->pipe_fd);
	wait_all_child(&pipex);
	return (0);
}

void	run_child(t_pipex *pipex, char **argv, size_t num_pipe)
{
	size_t				add_pipe;
	t_pipe_node *const	head = pipex->pipe_list.head;
	t_pipe_node *const	tail = pipex->pipe_list.tail;

	head->process_id = \
		run_child_to_file(pipex, argv, READ, FIRST_CMD);
	add_pipe = run_multiple_pipes(pipex, num_pipe);
	tail->process_id = \
		run_child_to_file(pipex, argv, WRITE, add_pipe + LAST_COMMAND);
}

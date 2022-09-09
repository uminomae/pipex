/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/09 10:12:56 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	t_pipex		pipex;
	size_t		num_pipe;

	begin_pipex(&pipex, argc, argv);
	open_files(&pipex, argc, argv, pipex.file_fd);
	num_pipe = make_pipe(&pipex, argc, NUM_OF_BASE);
	run_child(&pipex, argv, num_pipe);
	close_both_fd(&pipex.v_argv, pipex.file_fd);
	close_both_fd(&pipex.v_argv, pipex.pipe_list.tail->pipe_fd);
	wait_all_child(&pipex);
	return (0);
}

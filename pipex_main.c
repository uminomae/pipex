/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/14 18:39:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	close_all_pipe(t_pipex *pipex)
{
	t_pipe_node	*node;

	node = pipex->pipe_list.head;
	while (node != NULL)
	{
		close_both_fd(pipex, node->pipe_fd);
		// x_waitpid(pipex, node->process_id);
		node = node->next;
	}
	// close_both_fd(pipex, node->pipe_fd);
}

// TODO みぎから
//TODO argc使用してるか
//closeをわけてみる
//親子の連続でやってみる
int	main(int argc, char **argv)
{
	t_pipex		pipex;
	size_t		num_pipe;

	begin_pipex(&pipex, argc, argv);
	num_pipe = make_pipe(&pipex, argc, pipex.normal_argc);
	open_files(&pipex, argc, argv);
	run_separate_child(&pipex, argv, num_pipe);
	close_both_fd(&pipex, pipex.file_fd);
	
	// x_close(&pipex, pipex.pipe_list.head->pipe_fd[WRITE]);
	// x_close(&pipex, pipex.pipe_list.head->pipe_fd[READ]);
	// x_close(&pipex, 1);
	// x_close(&pipex, 0);
	// x_close(&pipex, pipex.pipe_list.tail->pipe_fd[WRITE]);
	// x_close(&pipex, pipex.pipe_list.tail->pipe_fd[READ]);
	close_all_pipe(&pipex);
	// close_both_fd(&pipex, pipex.pipe_list.head->pipe_fd);
	// close_both_fd(&pipex, pipex.pipe_list.tail->pipe_fd);
	wait_all_child(&pipex);
	exit_success(&pipex);
}

//preparation :make infile
// 
// for ((i=0; i<100; i++)); do
//    echo "abcdefghijk"
//  done >infile
// for ((i=0; i<65537; i++)); do
//    echo 'a'
//  done | tr -d '\n' >infile65537
//
//samle test:
// 
//./pipex infile "ls -l" "wc -l " outfile1
//< infile ls -l | wc -l > outfile2
// 
//./pipex here_doc LIMITER "cat" "grep a" out_heredoc
//cat << LIMITER | grep a >> out_heredoc
//
//./pipex infile "none" "./cmd_name" outfile1
//< infile none | ./cmd_name > outfile2
// 
//leak test: 
// 
//system("leaks -q pipex");

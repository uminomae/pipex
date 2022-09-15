/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/15 18:36:25 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_separate_child2(t_pipex *pipex);

// TODO みぎから
//TODO argc使用してるか
int	main(int argc, char **argv)
{
	t_pipex		pipex;
	//size_t		num_pipe;

	begin_pipex(&pipex, argc, argv);
	//num_pipe = make_pipe(&pipex, argc, pipex.normal_argc);
	open_files(&pipex, argc, argv);
	//run_separate_child(&pipex, argv, num_pipe);
	run_separate_child2(&pipex);
	close_both_fd(&pipex, pipex.file_fd);
	close_both_fd(&pipex, pipex.pipe_list.tail->pipe_fd);
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

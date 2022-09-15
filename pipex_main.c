/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/15 20:36:27 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	dup_file_fd_std_in_out(t_pipex *pipex)
{
	x_dup2(pipex, pipex->file_fd[READ], STDIN_FILENO);
	x_dup2(pipex, pipex->file_fd[WRITE], STDOUT_FILENO);
	close_both_fd(pipex, pipex->file_fd);
}

int	main(int argc, char **argv)
{
	t_pipex		pipex;

	begin_pipex(&pipex, argc, argv);
	open_files(&pipex, argc, argv);
	dup_file_fd_std_in_out(&pipex);
	run_child_recursive(&pipex, 0);
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

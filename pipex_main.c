/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/12/30 19:04:34 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	t_pipex		pipex;

	begin_pipex(&pipex, argc, argv);
	open_files_and_dup(&pipex, argc, argv);
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
// valgrind --leak-check=full ./pipex Makefile "grep NAME" "wc -l" res

// ./pipex Makefile "/ban/cat" "grep NAME" res のケースで、
// pipex_run_make_v_argv.c63行目のx_strdupがLeakしました。
// また、./pipex Makefile "" "grep NAME" resなどしたとき、
// command not found: command name is null charが2回表示されていました。

// ./pipex here_doc "cat" "grep a" out_heredoc
//でcrash
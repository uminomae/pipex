/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/04 13:34:22 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//TODO pipe_nどうする？
int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	size_t	i;
	//int 	pipe_n[2];
	//size_t	multiple_pipes;
	
	begin_pipex(&pipex, argc, argv, env);
	run_child_to_file(&pipex, argv, READ, 2);
	i = run_multiple_pipes(&pipex, argc, argv);
	//multiple_pipes = (size_t)argc - 5;
	//i = 0;
	//while (i < multiple_pipes)
	//{
	//	create_pipe_fd(pipe_n, &pipex.v_argv);
	//	run_child_to_pipe(&pipex, argv, pipex.pipe_fd, pipe_n, i);
	//	i++;
	//}
	run_child_to_file(&pipex, argv, WRITE, i + 3);
	return (0);
}

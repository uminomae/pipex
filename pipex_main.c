/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/04 13:21:26 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//static void	create_pipe_fd(int *pipe_fd, t_v_argv *v_argv);

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	size_t	i;
	int 	pipe_n[2];

	begin_pipex(&pipex, argc, argv, env);
	run_child_to_file(&pipex, argv, READ, 2);
	i = 0;
	while (i < (size_t)argc - 5)
	{
		create_pipe_fd(pipe_n, &pipex.v_argv);
		run_child_to_pipe(&pipex, argv, pipex.pipe_fd, pipe_n, i);
		i++;
	}
	run_child_to_file(&pipex, argv, WRITE, i + 3);
	return (0);
}

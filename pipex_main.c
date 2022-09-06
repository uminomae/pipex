/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/07 00:16:24 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe_fd(int *pipe_fd, t_v_argv *v_argv)
{
	int	ret;

	ret = pipe(pipe_fd);
	if (ret == ERR_NUM)
		exit_with_error(v_argv, ERR_MSG_PIPE);
}

void	make_pipe(t_pipex pipex)
{
	create_pipe_fd(pipex->pipe_fd, &pipex->v_argv);
	
}


int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	size_t	add_pipes;

	begin_pipex(&pipex, argc, argv, env);
	make_pipe(&pipex);
	run_child_to_file(&pipex, argv, READ, FIRST_CMD);
	add_pipes = run_multiple_pipes(&pipex, argc);
	run_child_to_file(&pipex, argv, WRITE, add_pipes + LAST_COMMAND);
	return (0);
}

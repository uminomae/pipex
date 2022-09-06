/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:49:55 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/07 00:16:22 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	validate_number_of_arguments(int argc);
static void	init_struct(t_pipex *pipex, int argc, char **argv, char **env);

void	begin_pipex(t_pipex *pipex, int argc, char **argv, char **env)
{
	validate_number_of_arguments(argc);
	init_struct(pipex, argc, argv, env);
	//create_pipe_fd(pipex->pipe_fd, &pipex->v_argv);
}

static void	validate_number_of_arguments(int argc)
{
	if (argc >= REQUIRED_NUM)
		return ;
	else
	{
		ft_putendl_fd(ERR_MSG_VALID, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

static void	init_struct(t_pipex *pipex, int argc, char **argv, char **env)
{
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->env = env;
	pipex->v_argv.list_absolute_path_of_command = NULL;
	pipex->v_argv.list_of_directry = NULL;
	pipex->v_argv.temp_devided_list = NULL;
	pipex->v_argv.virtual_argv = NULL;
}

//void	create_pipe_fd(int *pipe_fd, t_v_argv *v_argv)
//{
//	int	ret;

//	ret = pipe(pipe_fd);
//	if (ret == ERR_NUM)
//		exit_with_error(v_argv, ERR_MSG_PIPE);
//}

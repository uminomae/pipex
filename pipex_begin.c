/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:49:55 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/09 08:41:45 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	validate_number_of_arguments(int argc);
static void	init_struct(t_pipex *pipex, int argc, char **argv);
//static void	init_struct(t_pipex *pipex, int argc, char **argv, char **env);

void	begin_pipex(t_pipex *pipex, int argc, char **argv)
//void	begin_pipex(t_pipex *pipex, int argc, char **argv, char **env)
{
	validate_number_of_arguments(argc);
	init_struct(pipex, argc, argv);
	//init_struct(pipex, argc, argv, env);
}

static void	validate_number_of_arguments(int argc)
{
	if (argc >= NUM_OF_BASE)
		return ;
	else
	{
		ft_putendl_fd(ERR_MSG_ARGC, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

static void	init_struct(t_pipex *pipex, int argc, char **argv)
//static void	init_struct(t_pipex *pipex, int argc, char **argv, char **env)
{
	pipex->argc = argc;
	pipex->argv = argv;
	//pipex->env = env;
	pipex->pipe_list.head = NULL;
	pipex->pipe_list.tail = NULL;
	pipex->v_argv.list_absolute_path_of_command = NULL;
	pipex->v_argv.list_of_directry = NULL;
	pipex->v_argv.temp_devided_list = NULL;
	pipex->v_argv.virtual_argv = NULL;
}

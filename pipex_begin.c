/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:49:55 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/10 09:55:09 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
   #include <stdlib.h>
   
static void	validate_argc(int argc);
static void	init_struct(t_pipex *pipex, char **argv);

void	begin_pipex(t_pipex *pipex, int argc, char **argv)
{
	validate_argc(argc);
	init_struct(pipex, argv);
}

static void	validate_argc(int argc)
{
	if (argc >= NUM_BASE)
		return ;
	else
	{
		ft_putendl_fd(ERR_MSG_ARGC, STDERR_FILENO);
	
		exit(EXIT_FAILURE);
	}
}

static void	init_struct(t_pipex *pipex, char **argv)
{
	pipex->argv = argv;
	pipex->pipe_list.head = NULL;
	pipex->pipe_list.tail = NULL;
	pipex->v_argv.list_absolute_path_of_command = NULL;
	pipex->v_argv.list_of_directory = NULL;
	pipex->v_argv.temp_divided_list = NULL;
	pipex->v_argv.virtual_argv = NULL;
}

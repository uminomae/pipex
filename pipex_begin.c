/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:49:55 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/10 16:22:57 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
   #include <stdlib.h>
   
static void	validate_argc(t_pipex *pipex, int argc);
static void	init_struct(t_pipex *pipex, char **argv);

static bool	is_here_doc(char **argv)
{
	if (ft_strncmp(argv[1], HERE_DOC_STR, ft_strlen(HERE_DOC_STR)) \
															== SAME_STRING)
		return (true);
	return (false);
}

void	begin_pipex(t_pipex *pipex, int argc, char **argv)
//void	begin_pipex(t_pipex *pipex, int argc, char **argv, size_t type)
{
	init_struct(pipex, argv);
	if (is_here_doc(argv) == true)
	{
		pipex->normal_argc = 6;
		pipex->other_cmd = 4;
	}
	else
	{
		pipex->normal_argc = 5;
		pipex->other_cmd = 3;
	}
	validate_argc(pipex, argc);
	init_pid_list(pipex, argc, pipex->other_cmd);
}

static void	validate_argc(t_pipex *pipex, int argc)
{
	if (argc >= (int)pipex->normal_argc)
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
	pipex->pid_list.head = NULL;
	pipex->pid_list.tail = NULL;
	pipex->v_argv.list_absolute_path_of_command = NULL;
	pipex->v_argv.list_of_directory = NULL;
	pipex->v_argv.temp_divided_list = NULL;
	pipex->v_argv.virtual_argv = NULL;
}

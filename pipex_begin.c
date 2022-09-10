/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:49:55 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/10 23:56:51 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	is_here_doc(char **argv);
static void	validate_argc(t_pipex *pipex, int argc);
static void	init_struct(t_pipex *pipex, char **argv);
static void	set_arg_position(t_pipex *pipex, char **argv);

void	begin_pipex(t_pipex *pipex, int argc, char **argv)
{
	init_struct(pipex, argv);
	set_arg_position(pipex, argv);
	validate_argc(pipex, argc);
	init_pid_list(pipex, argc, pipex->other_cmd);
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

static void	set_arg_position(t_pipex *pipex, char **argv)
{
	if (is_here_doc(argv) == true)
	{
		pipex->is_here_doc = true;
		pipex->normal_argc = 6;
		pipex->other_cmd = 4;
		pipex->first_cmd = 3;
		pipex->last_cmd = 4;
	}
	else
	{
		pipex->is_here_doc = false;
		pipex->normal_argc = 5;
		pipex->other_cmd = 3;
		pipex->first_cmd = 2;
		pipex->last_cmd = 3;
	}
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

static bool	is_here_doc(char **argv)
{
	if (ft_strncmp(argv[1], HERE_DOC_STR, ft_strlen(HERE_DOC_STR)) \
															== SAME_STRING)
		return (true);
	return (false);
}

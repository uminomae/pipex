/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:49:55 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/14 12:26:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	validate_variables(t_pipex *pipex, int argc, char **argv);
static void	init_struct(t_pipex *pipex, int argc, char **argv);
static void	set_arg_position(t_pipex *pipex, char **argv);

void	begin_pipex(t_pipex *pipex, int argc, char **argv)
{
	validate_variables(pipex, argc, argv);
	init_struct(pipex, argc, argv);
	set_arg_position(pipex, argv);
	init_pid_list(pipex, argc, pipex->other_cmd);
}

static void	validate_variables(t_pipex *pipex, int argc, char **argv)
{
	if (argv == NULL)
		exit_with_error(pipex, "argv", TYPE_ARGV_NULL, false);
	if (environ == NULL)
		exit_with_error(pipex, "environ", TYPE_ENV_NULL, false);
	if (argc < NUM_ARGC_REQUIRED)
		exit_with_error(pipex, "argc", TYPE_ARGC, false);
	else
		return ;
}

static void	init_struct(t_pipex *pipex, int argc, char **argv)
{
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->pipe_list.head = NULL;
	pipex->pipe_list.tail = NULL;
	pipex->pid_list.head = NULL;
	pipex->pid_list.tail = NULL;
	pipex->alloc_list.head = NULL;
	pipex->alloc_list.tail = NULL;
	pipex->v_argv.list_abs_path_cmd = NULL;
	pipex->v_argv.list_of_directory = NULL;
	pipex->v_argv.temp_divided_list = NULL;
	pipex->v_argv.virtual_argv = NULL;
}

static bool	is_here_doc(char **argv)
{
	if (ft_strncmp(argv[1], HERE_DOC_STR, ft_strlen(HERE_DOC_STR)) \
															== SAME_STRING)
		return (true);
	return (false);
}

static void	set_arg_position(t_pipex *pipex, char **argv)
{
	if (is_here_doc(argv) == true)
	{
		pipex->is_here_doc = true;
		pipex->normal_argc = 6;
		pipex->other_cmd = 4;
		pipex->first_cmd_idx = 3;
		pipex->last_cmd_idx = 4;
	}
	else
	{
		pipex->is_here_doc = false;
		pipex->normal_argc = 5;
		pipex->other_cmd = 3;
		pipex->first_cmd_idx = 2;
		pipex->last_cmd_idx = 3;
	}
}



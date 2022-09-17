/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:49:55 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/16 23:22:14 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	validate_variables(t_pipex *pipex, int argc, char **argv);
static void	init_struct(t_pipex *pipex, int argc, char **argv);
static bool	is_here_doc(char **argv);
static void	set_arg_position(t_pipex *pipex, char **argv);


//TODO free
// TODO init
void	get_cmd_name(t_pipex *pipex, size_t times)
{
	size_t	i;
	// size_t	times;
	char	**argv_n;
	t_cmd_node	*node;

	node = pipex->cmd_list.head;
	// times = pipex->argc - pipex->other_cmd;
	i = 0;
	while (i < times)
	{
		argv_n = split_cmd_name_and_option(\
			pipex, pipex->argv[pipex->first_cmd_idx + i]);
		if (argv_n == NULL)
			exit_with_error(pipex, node->cmd, TYPE_CMD_NOT_FOUND, false);			
		if (ft_strlen(argv_n[0]) == 0)
			exit_with_error(pipex, node->cmd, TYPE_CMD_NOT_FOUND, false);
		node->cmd = x_strdup(pipex, argv_n[0]);
		free(argv_n);
		node = node->next;
	}
}

void	validate_cmd(t_pipex *pipex)
{
	size_t	times;

	
	times = pipex->argc - pipex->other_cmd;
	get_cmd_name(pipex, times);
}

void	begin_pipex(t_pipex *pipex, int argc, char **argv)
{
	validate_variables(pipex, argc, argv);
	init_struct(pipex, argc, argv);
	set_arg_position(pipex, argv);
	init_pid_list(pipex, argc, pipex->other_cmd);
	init_cmd_list(pipex, argc, pipex->other_cmd);
	// validate_cmd(pipex);
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

static bool	is_here_doc(char **argv)
{
	if (ft_strncmp(argv[1], HERE_DOC_STR, ft_strlen(HERE_DOC_STR)) \
															== SAME_STRING)
		return (true);
	return (false);
}

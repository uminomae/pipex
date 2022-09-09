/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:49:55 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/09 17:00:24 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	validate_argc(int argc);
static void	init_struct(t_pipex *pipex, char **argv);

bool	is_here_doc(char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc") == SAME_STRING)
		return (true);
	return (false);
}

void	begin_pipex(t_pipex *pipex, int argc, char **argv)
{
	if (is_here_doc(argv) == true)
	{
		
		validate_argc(argc, NUM_HEREDOC_BASE);
	}
	else
		validate_argc(argc, NUM_BASE);
	init_struct(pipex, argv);
}

static void	validate_argc(int argc, int num_base)
{
	if (argc >= num_base)
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
	pipex->v_argv.temp_devided_list = NULL;
	pipex->v_argv.virtual_argv = NULL;
}

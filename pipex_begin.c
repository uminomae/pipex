/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:49:55 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/04 10:14:20 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validate_number_of_arguments(int argc)
{
	if (argc == 5)
		return ;
	else
	{
		ft_putendl_fd("error : 5 arguments are required", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	init_struct(t_pipex *pipex, int argc, char **argv, char **env)
{
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->env = env;
	pipex->v_argv.list_absolute_path_of_command = NULL;
	pipex->v_argv.list_of_directry = NULL;
	pipex->v_argv.temp_devided_list = NULL;
	pipex->v_argv.virtual_argv = NULL;
}

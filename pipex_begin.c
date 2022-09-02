/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:49:55 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/02 15:40:45 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validate_value(int argc)
{
	if (argc == 5)
		return ;
	else
	{
		//TODO func
		perror("argc");
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

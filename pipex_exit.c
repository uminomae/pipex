/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:20 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/02 16:03:30 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_struct(t_pipex *pipex)
{
	free_list_absolute_path_of_command(&pipex->v_argv);
	free_virtual_argv(&pipex->v_argv);
	free_list_of_directry(&pipex->v_argv);
	free_temp_devided_list(&pipex->v_argv);
}

void	exit_successfully_child_process(t_pipex *pipex)
{
	free_struct(pipex);
	exit(EXIT_FAILURE);
}

void	exit_with_error_child_process(t_pipex *pipex, char *str)
{
	free_struct(pipex);
	perror(str);
	exit(EXIT_FAILURE);
}

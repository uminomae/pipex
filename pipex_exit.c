/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:20 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/01 00:58:06 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_free_together(t_pipex *pipex)
{
	free_list_absolute_path_of_command(&pipex->v_argv);
	free_virtual_argv(&pipex->v_argv);
	free_list_of_directry(&pipex->v_argv);
	free_temp_devided_list(&pipex->v_argv);
}

void	exit_successfully_child_process(t_pipex *pipex)
{
	set_free_together(pipex);
	_exit(EXIT_FAILURE);
}

void	exit_with_error_child_process(t_pipex *pipex, char *str)
{
	set_free_together(pipex);
	perror(str);
	_exit(EXIT_FAILURE);
}

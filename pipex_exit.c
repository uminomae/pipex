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

//TODO
static void	free_struct(t_v_argv *v_argv)
//static void	free_struct(t_pipex *pipex)
{
	free_list_absolute_path_of_command(v_argv);
	free_virtual_argv(v_argv);
	free_list_of_directry(v_argv);
	free_temp_devided_list(v_argv);
}
//{
//	free_list_absolute_path_of_command(&pipex->v_argv);
//	free_virtual_argv(&pipex->v_argv);
//	free_list_of_directry(&pipex->v_argv);
//	free_temp_devided_list(&pipex->v_argv);
//}

void	exit_successfully(t_pipex *pipex)
{
	free_struct(&pipex->v_argv);
	exit(EXIT_FAILURE);
}

void	exit_with_error(t_pipex *pipex, char *str)
{
	free_struct(&pipex->v_argv);
	perror(str);
	exit(EXIT_FAILURE);
}

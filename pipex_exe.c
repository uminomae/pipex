/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:31 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/08 15:46:07 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	x_execve(t_pipex *pipex, char **virtual_argv)
{
	int	ret;
	
	ret = execve(virtual_argv[ABS_PATH_CMD], virtual_argv, pipex->env);
	if (ret == ERR_NUM)
		exit_with_error(&pipex->v_argv, ERR_MSG_EXCECVE);
}
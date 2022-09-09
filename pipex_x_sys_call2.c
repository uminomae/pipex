/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_x_sys_call2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/09 10:19:05 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	x_close(t_v_argv *v_argv, int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == ERR_NUM)
		exit_with_error(v_argv, ERR_MSG_CLOSE);
}

void	x_execve(t_pipex *pipex, char **virtual_argv)
{
	int	ret;

	ret = execve(virtual_argv[ABS_PATH_CMD], virtual_argv, environ);
	if (ret == ERR_NUM)
		exit_with_error(&pipex->v_argv, ERR_MSG_EXCECVE);
}

void	x_waitpid(t_v_argv *v_argv, pid_t process_id)
{
	pid_t	ret;
	int		child_status;

	ret = waitpid(process_id, &child_status, GROUP_OF_CALLER);
	if (ret == ERR_NUM)
		exit_with_error(v_argv, ERR_MSG_WAITPID);
}

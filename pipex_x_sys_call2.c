/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_x_sys_call2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/13 04:23:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	x_close(t_pipex *pipex, int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_CLOSE, 1);
}

void	x_execve(t_pipex *pipex, char **virtual_argv)
{
	int	ret;

	ret = execve(virtual_argv[ABS_PATH_CMD], virtual_argv, environ);
	if (ret == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_EXCECVE, 1);
}

void	x_waitpid(t_pipex *pipex, pid_t process_id)
{
	pid_t	ret;
	int		child_status;

	ret = waitpid(process_id, &child_status, GROUP_OF_CALLER);
	if (ret == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_WAITPID, 1);
}

void	x_unlink(t_pipex *pipex, char *file_name)
{
	int	ret;

	ret = unlink(file_name);
	if (ret == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_UNLINK, 1);
}

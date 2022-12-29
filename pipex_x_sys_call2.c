/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_x_sys_call2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:07 by hioikawa          #+#    #+#             */
/*   Updated: 2022/12/29 02:22:49 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	x_waitpid(t_pipex *pipex, pid_t process_id)
{
	pid_t	ret;
	int		child_status;

	ret = waitpid(process_id, &child_status, GROUP_OF_CALLER);
	if (ret == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_WAITPID, TYPE_PERROR, true);
}

void	x_unlink(t_pipex *pipex, char *file_name)
{
	int	ret;

	ret = unlink(file_name);
	if (ret == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_UNLINK, TYPE_PERROR, true);
}

void	x_access(t_pipex *pipex, char *file_name)
{
	int	ret;

	ret = access(file_name, X_OK);
	if (ret == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_ACCESS, TYPE_PERROR, true);
}
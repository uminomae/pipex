/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_create_wait.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:31 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/07 01:45:24 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	create_child_process_by_fork_func(t_pipex *pipex)
{
	pid_t	ret;

	ret = fork();
	if (ret == ERR_NUM)
	{
		close_both_pipe(&pipex->v_argv, pipex->pipe_list.head->pipe_fd);
		exit_with_error(&pipex->v_argv, ERR_MSG_FORK);
	}
	return (ret);
}

void	wait_pid_for_child_process(t_v_argv *v_argv, pid_t process_id)
{
	pid_t	ret;
	int		child_status;

	ret = waitpid(process_id, &child_status, GROUP_OF_CALLER);
	if (ret == ERR_NUM)
		exit_with_error(v_argv, ERR_MSG_WAITPID);
}

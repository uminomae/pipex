/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/08 15:23:49 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	duplicate_to_standard_in_out(\
			t_v_argv *v_argv, int fd_for_read, int fd_for_write);
			
pid_t	run_child_to_file(\
				t_pipex *pipex, char **argv, int read_or_write, int argv_idx)
{
	int *const			file_fd = pipex->file_fd;
	t_v_argv			*v_argv;
	pid_t				process_id;
	int			ret;
	char		**virtual_argv;
	
	virtual_argv = NULL;
	v_argv = &pipex->v_argv;
	process_id = create_child_process_by_fork_func(pipex);
	if (process_id == CHILD_PROCESS)
	{
		if (read_or_write == READ)
		{
			x_dup2(v_argv, file_fd[READ], STDIN_FILENO);
			x_dup2(v_argv, pipex->pipe_list.head->pipe_fd[WRITE], STDOUT_FILENO);
			close_both_pipe(v_argv, pipex->pipe_list.head->pipe_fd);
		}
		else if (read_or_write == WRITE)
		{
			x_dup2(v_argv, pipex->pipe_list.tail->pipe_fd[READ], STDIN_FILENO);
			x_dup2(v_argv, file_fd[WRITE], STDOUT_FILENO);
			close_both_pipe(v_argv, pipex->pipe_list.tail->pipe_fd);
		}
		virtual_argv = get_virtual_argv(pipex, argv[argv_idx]);
		ret = execve(virtual_argv[ABS_PATH_CMD], virtual_argv, pipex->env);
		if (ret == ERR_NUM)
			exit_with_error(&pipex->v_argv, ERR_MSG_EXCECVE);
	}
	return (process_id);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:31 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/08 15:00:18 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//void	duplicate_to_standard_in_out(\
//			t_v_argv *v_argv, int fd_for_read, int fd_for_write)
//{
//	x_dup2(v_argv, fd_for_read, STDIN_FILENO);
//	x_dup2(v_argv, fd_for_write, STDOUT_FILENO);
//}

void	x_dup2(t_v_argv *v_argv, int file, int fd)
{
	int	ret;

	ret = dup2(file, fd);
	if (ret == ERR_NUM)
		exit_with_error(v_argv, ERR_MSG_DUP2);
}

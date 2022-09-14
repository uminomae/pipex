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

//void	exit_success(t_pipex *pipex)
//{
//	free_struct(pipex);
//	exit(EXIT_SUCCESS);
//}

void	exit_with_error(t_pipex *pipex, char *str, size_t type)
{
	if (type == TYPE_CMD_NOT_FOUND)
	{
		if (ft_strchr(str, SIGN_ABS_PATH) == NULL)
			exit_put_msg_cmd_not_found(pipex, str);
		else
			perror(str);
	}
	else if (type == TYPE_ENV_NULL)
		ft_putendl_fd(ERR_MSG_ENVIRON, STDERR_FILENO);
	else
		perror(str);
	free_struct(pipex);
	exit(EXIT_FAILURE);
}

void	exit_put_msg_cmd_not_found(t_pipex *pipex, char *command_from_argv)
{
	ft_putstr_fd(ERR_MSG_CMD_NOT_FOUND, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(command_from_argv, STDERR_FILENO);
	free_struct(pipex);
	exit(EXIT_FAILURE);
}

void	exit_put_msg_argv(void)
{
	ft_putendl_fd(ERR_MSG_ARGV, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	exit_put_msg_envp(void)
{
	ft_putendl_fd(ERR_MSG_ENVIRON, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	exit_put_msg_err_argc(void)
{
	ft_putendl_fd(ERR_MSG_ARGC, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

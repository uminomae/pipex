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

void	exit_success(t_pipex *pipex)
{
	free_struct(pipex);
	exit(EXIT_SUCCESS);
}

static void put_error_msg(size_t type)
{
	if (type == TYPE_ENV_NULL)
		ft_putendl_fd(ERR_MSG_ENVIRON, STDERR_FILENO);
	else if (type == TYPE_ARGV_NULL)
		ft_putendl_fd(ERR_MSG_ARGV, STDERR_FILENO);
	else if (type == TYPE_ARGC)
		ft_putendl_fd(ERR_MSG_ARGC, STDERR_FILENO);
	else if (type == TYPE_ARGC_HEREDOC)
		ft_putendl_fd(ERR_MSG_ARGC_HEREDOC, STDERR_FILENO);
	else if (type == TYPE_LIMITER_NULL)
		ft_putendl_fd(ERR_MSG_LIMITER_NULL_CHAR, STDERR_FILENO);
	else if (type == TYPE_FT)
		ft_putendl_fd(ERR_MSG_FT, STDERR_FILENO);
	else
		ft_putendl_fd(ERR_MSG_FT, STDERR_FILENO);
}

void	exit_with_error(t_pipex *pipex, char *str, size_t type, bool need_free)
{
	if (type == TYPE_PERROR)
		perror(str);
	else if (type == TYPE_CMD_NOT_FOUND)
	{
		if (ft_strchr(str, SIGN_ABS_PATH) == NULL)
			exit_put_msg_cmd_not_found(str);
		else if (ft_strncmp(str, "", 1))
			exit_put_msg_cmd_not_found(str);
		else
			perror(str);
	}
	else
		put_error_msg(type);
	if (need_free == true)
		free_struct(pipex);
	exit(EXIT_FAILURE);
}

void	exit_put_msg_cmd_not_found(char *str)
{
	ft_putstr_fd(ERR_MSG_CMD_NOT_FOUND, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

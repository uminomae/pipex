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

void	safe_free(char **malloc_ptr)
{
	free(*malloc_ptr);
	*malloc_ptr = NULL;
}

//void	exit_successfully(t_arg *v_argv)
//{
//	free_struct(v_argv);
//	exit(EXIT_FAILURE);
//}

void	exit_with_error(t_arg *v_argv, char *str)
{
	free_struct(v_argv);
	perror(str);

	exit(EXIT_FAILURE);
}

void	exit_err_cmd_access(t_arg *v_argv, char *command_from_argv)
{
	free_struct(v_argv);

	if (ft_strchr(command_from_argv, SIGN_ABS_PATH) == NULL)
	{
		ft_putstr_fd(ERR_MSG_CMD_NOT_FOUND, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		free_struct(v_argv);
		ft_putendl_fd(command_from_argv, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else
		exit_with_error(v_argv, ERR_MSG_ACCESS);
}

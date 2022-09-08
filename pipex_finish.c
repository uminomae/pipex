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

void	exit_successfully(t_v_argv *v_argv)
{
	free_struct(v_argv);
	exit(EXIT_FAILURE);
}

void	exit_with_error(t_v_argv *v_argv, char *str)
{
	free_struct(v_argv);
	perror(str);
	exit(EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:23 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/01 00:58:19 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	safe_free(char **malloc_ptr)
{
	free(*malloc_ptr);
	*malloc_ptr = NULL;
}

void	free_temp_devided_list(t_v_argv *v)
{
	size_t	i;

	i = 0;
	if (v->temp_devided_list == NULL)
		return ;
	while (v->temp_devided_list[i] != NULL)
	{
		free(v->temp_devided_list[i]);
		v->temp_devided_list[i] = NULL;
		i++;
	}
	free(v->temp_devided_list[i]);
	free(v->temp_devided_list);
}

void	free_list_of_directry(t_v_argv *v)
{
	size_t	i;

	i = 0;
	if (v->list_of_directry == NULL || v->list_of_directry[i] == NULL)
		return ;
	while (v->list_of_directry[i] != NULL)
	{
		free(v->list_of_directry[i]);
		v->list_of_directry[i] = NULL;
		i++;
	}
	free(v->list_of_directry[i]);
	free(v->list_of_directry);
}

void	free_virtual_argv(t_v_argv *v)
{
	size_t	i;

	i = 0;
	if (v->virtual_argv == NULL)
		return ;
	while (v->virtual_argv[i] != NULL)
	{
		free(v->virtual_argv[i]);
		v->virtual_argv[i] = NULL;
		i++;
	}
	free(v->virtual_argv[i]);
	free(v->virtual_argv);
}

void	free_list_absolute_path_of_command(t_v_argv *v)
{
	size_t	i;

	i = 0;
	if (v->list_absolute_path_of_command == NULL)
		return ;
	while (v->list_absolute_path_of_command[i] != NULL)
	{
		free(v->list_absolute_path_of_command[i]);
		v->list_absolute_path_of_command[i] = NULL;
		i++;
	}
	free(v->list_absolute_path_of_command[i]);
	free(v->list_absolute_path_of_command);
}

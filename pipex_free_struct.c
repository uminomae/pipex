/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:23 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/10 09:42:30 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_temp_divided_list(t_v_argv *v);
static void	free_list_of_directory(t_v_argv *v);
static void	free_virtual_argv(t_v_argv *v);
static void	free_list_absolute_path_of_command(t_v_argv *v);

void	free_struct(t_v_argv *v_argv)
{
	free_list_absolute_path_of_command(v_argv);
	free_virtual_argv(v_argv);
	free_list_of_directory(v_argv);
	free_temp_divided_list(v_argv);
}

static void	free_list_absolute_path_of_command(t_v_argv *v)
{
	size_t	i;

	i = 0;
	if (v->list_absolute_path_of_command == NULL)
		return ;
	while (v->list_absolute_path_of_command[i] != NULL)
	{
		safe_free(&v->list_absolute_path_of_command[i]);
		i++;
	}
	free(v->list_absolute_path_of_command[i]);
	free(v->list_absolute_path_of_command);
	v->list_absolute_path_of_command = NULL;
}

static void	free_temp_divided_list(t_v_argv *v)
{
	size_t	i;

	i = 0;
	if (v->temp_divided_list == NULL)
		return ;
	while (v->temp_divided_list[i] != NULL)
	{
		safe_free(&v->temp_divided_list[i]);
		i++;
	}
	free(v->temp_divided_list[i]);
	free(v->temp_divided_list);
	v->temp_divided_list = NULL;
}

static void	free_list_of_directory(t_v_argv *v)
{
	size_t	i;

	i = 0;
	if (v->list_of_directory == NULL || v->list_of_directory[i] == NULL)
		return ;
	while (v->list_of_directory[i] != NULL)
	{
		safe_free(&v->list_of_directory[i]);
		i++;
	}
	free(v->list_of_directory[i]);
	free(v->list_of_directory);
	v->list_of_directory = NULL;
}

static void	free_virtual_argv(t_v_argv *v)
{
	size_t	i;

	i = 0;
	if (v->virtual_argv == NULL)
		return ;
	while (v->virtual_argv[i] != NULL)
	{
		safe_free(&v->virtual_argv[i]);
		i++;
	}
	free(v->virtual_argv[i]);
	free(v->virtual_argv);
	v->virtual_argv = NULL;
}

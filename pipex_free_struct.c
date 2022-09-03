/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:23 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/03 03:05:56 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_temp_devided_list(t_v_argv *v);
static void	free_list_of_directry(t_v_argv *v);
static void	free_virtual_argv(t_v_argv *v);
static void	free_list_absolute_path_of_command(t_v_argv *v);

void	free_struct(t_v_argv *v_argv)
{
	free_list_absolute_path_of_command(v_argv);
	free_virtual_argv(v_argv);
	free_list_of_directry(v_argv);
	free_temp_devided_list(v_argv);
}

static void	free_temp_devided_list(t_v_argv *v)
{
	size_t	i;

	i = 0;
	if (v->temp_devided_list == NULL)
		return ;
	while (v->temp_devided_list[i] != NULL)
	{
		safe_free(&v->temp_devided_list[i]);
		i++;
	}
	free(v->temp_devided_list[i]);
	free(v->temp_devided_list);
	v->temp_devided_list = NULL;
}

static void	free_list_of_directry(t_v_argv *v)
{
	size_t	i;

	i = 0;
	if (v->list_of_directry == NULL || v->list_of_directry[i] == NULL)
		return ;
	while (v->list_of_directry[i] != NULL)
	{
		safe_free(&v->list_of_directry[i]);
		i++;
	}
	free(v->list_of_directry[i]);
	free(v->list_of_directry);
	v->list_of_directry = NULL;
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

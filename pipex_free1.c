/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:23 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/13 10:23:35 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_temp_divided_list(t_arg *v);
static void	free_list_of_directory(t_arg *v);
static void	free_virtual_argv(t_arg *v);
static void	free_list_absolute_path_of_command(t_arg *v);

void	free_struct(t_pipex *pipex)
{
	free_list_absolute_path_of_command(&pipex->v_argv);
	free_virtual_argv(&pipex->v_argv);
	free_list_of_directory(&pipex->v_argv);
	free_temp_divided_list(&pipex->v_argv);
	free_alloc_list(&pipex->alloc_list);
}

static void	free_list_absolute_path_of_command(t_arg *v)
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

static void	free_temp_divided_list(t_arg *v)
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

static void	free_list_of_directory(t_arg *v)
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

static void	free_virtual_argv(t_arg *v)
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

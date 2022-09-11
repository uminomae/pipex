/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/11 19:03:10 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//void	test_print(t_pipex *pipex)
//{
//	t_alloc_node	*node;
//	size_t			i;

//	i = 0;
//	if (pipex->alloc_list.head == NULL)
//		return ;
//	node = pipex->alloc_list.head;
//	while (node != NULL)
//	{
//		printf("%zu: %p\n",i, node->ptr);
//		node = node->next;
//		i++;
//	}
//}

int	main(int argc, char **argv)
{
	t_pipex		pipex;
	size_t		num_pipe;

	begin_pipex(&pipex, argc, argv);
	num_pipe = make_pipe(&pipex, argc, pipex.normal_argc);
	open_files(&pipex, argc, argv);
	run_separate_child(&pipex, argv, num_pipe);
	close_both_fd(&pipex, pipex.file_fd);
	close_both_fd(&pipex, pipex.pipe_list.tail->pipe_fd);
	wait_all_child(&pipex);
	//
	//test_print(&pipex);
	//
	free_struct(&pipex);
	//
	//test_print(&pipex);
	//
	//
	//pipex.alloc_list.head = malloc(10);
	system("leaks -q pipex");
	//
	return (0);
}

void	run_separate_child(t_pipex *pipex, char **argv, size_t num_pipe)
{
	size_t				add_pipe;
	t_pid_node *const	head = pipex->pid_list.head;
	t_pid_node *const	tail = pipex->pid_list.tail;

	head->process_id = \
		run_child_to_file(pipex, argv, READ, pipex->first_cmd);
	add_pipe = run_multiple_pipes(pipex, num_pipe);
	tail->process_id = \
		run_child_to_file(pipex, argv, WRITE, add_pipe + pipex->last_cmd);
}

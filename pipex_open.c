/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:31 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/11 08:36:25 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_read_file(t_pipex *pipex ,char *argv);
static int	open_write_file(t_pipex *pipex, char *argv);

static void	run_child_to_file_read2(t_pipex *pipex)
{
	x_dup2(pipex, pipex->file_fd[READ], STDIN_FILENO);
	x_dup2(pipex, \
		pipex->pipe_list.head->pipe_fd[WRITE], STDOUT_FILENO);
	close_both_fd(pipex, pipex->pipe_list.head->pipe_fd);
}

static void	run_child_to_file_write2(t_pipex *pipex)
{
	x_dup2(pipex, \
				pipex->pipe_list.tail->pipe_fd[READ], STDIN_FILENO);
	x_dup2(pipex, pipex->file_fd[WRITE], STDOUT_FILENO);
	close_both_fd(pipex, pipex->pipe_list.tail->pipe_fd);
}

pid_t	run_child_to_file2(\
				t_pipex *pipex, char **argv, int read_or_write, int argv_idx)
{
	pid_t		process_id;

	process_id = x_fork(pipex);
	if (process_id == CHILD_PROCESS)
	{
		if (read_or_write == READ)
			run_child_to_file_read2(pipex);
		else if (read_or_write == WRITE)
			run_child_to_file_write2(pipex);
		get_path(pipex, &pipex->v_argv);
		pipex->v_argv.virtual_argv = \
			make_virtual_argv(pipex, &pipex->v_argv, argv[argv_idx]);
		x_execve(pipex, pipex->v_argv.virtual_argv);
	}
	return (process_id);
}

void	run_separate_child2(t_pipex *pipex, char **argv, size_t num_pipe)
{
	size_t				add_pipe;
	t_pid_node *const	head = pipex->pid_list.head;
	t_pid_node *const	tail = pipex->pid_list.tail;

	head->process_id = \
		run_child_to_file2(pipex, argv, READ,  pipex->first_cmd);
	add_pipe = run_multiple_pipes(pipex, num_pipe);
	tail->process_id = \
		run_child_to_file2(pipex, argv, WRITE, add_pipe + pipex->last_cmd);
}

int	make_file_here_doc(t_pipex *pipex)
{
	int	fd;

	fd = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_OPEN, 1);
	return (fd);
}

//TODO err
void	open_case_here_doc(t_pipex *pipex, int argc, char **argv)
{
	size_t	last_index;
	char	*word;
	char 	*str;
	int 	fd;
	char *temp;
	
	last_index = argc - 1;
	fd = make_file_here_doc(pipex);

	str = "";
   	while (1)
   	{
		ft_putstr_fd("pipe heredoc> ", 1);
   	    word = get_next_line(STDIN_FILENO);
		temp = str;
		if (ft_strncmp(word, argv[2], ft_strlen(word) - 1) == SAME_STRING)
		{
   	    	//free(temp);
			break;
		}
		str = x_strjoin(pipex, str, word);
   	    //free(temp);
		free(word);
   	}
	ft_putstr_fd(str, fd);
	x_close(pipex, fd);
	pipex->file_fd[READ] = open_read_file(pipex, ".here_doc");
	pipex->file_fd[WRITE] = open_write_file(pipex, argv[last_index]);
}

void	open_files(t_pipex *pipex, int argc, char *const *argv)
{
	size_t	last_index;

	last_index = argc - 1;
	pipex->file_fd[READ] = open_read_file(pipex, argv[FILE_FOR_READ]);
	pipex->file_fd[WRITE] = open_write_file(pipex, argv[last_index]);
}

static int	open_read_file(t_pipex *pipex ,char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY | O_CLOEXEC);
	if (fd == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_OPEN, 1);
	return (fd);
}

//file[WRITE] is like a chmod 644 
static int	open_write_file(t_pipex *pipex, char *argv)
{
	int	fd;

	fd = open(argv, O_WRONLY | O_CLOEXEC | O_CREAT | O_TRUNC, \
							S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_OPEN, 1);
	return (fd);

}

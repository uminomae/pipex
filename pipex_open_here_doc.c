/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open_here_doc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:31 by hioikawa          #+#    #+#             */
/*   Updated: 2022/12/29 04:20:56 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	create_file_here_doc_tmp(t_pipex *pipex, char *file_name);
static char	*to_empty(char *s);
static void	make_content_here_doc(t_pipex *pipex, char **argv, int fd);
static int	open_here_doc_write_file(t_pipex *pipex, char *argv);

void	open_here_doc(t_pipex *pipex, int argc, char **argv)
{
	size_t	last_index;
	int		fd;

	last_index = argc - 1;
	fd = create_file_here_doc_tmp(pipex, HERE_DOC_FILE);
	make_content_here_doc(pipex, argv, fd);
	pipex->file_fd[READ] = open_read_file(pipex, HERE_DOC_FILE);
	x_unlink(pipex, HERE_DOC_FILE);
	pipex->file_fd[WRITE] = open_here_doc_write_file(pipex, argv[last_index]);
}

static int	create_file_here_doc_tmp(t_pipex *pipex, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, \
							S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_OPEN, TYPE_PERROR, true);
	return (fd);
}

static void	make_content_here_doc(t_pipex *pipex, char **argv, int fd)
{
	char	*line;
	char	*limiter;

	limiter = x_strjoin(pipex, to_empty(argv[2]), LINE_FEED);
	while (1)
	{
		ft_putstr_fd(PRONMPT, 1);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(line)) == SAME_STRING)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(limiter);
	x_close(pipex, fd);
}

static int	open_here_doc_write_file(t_pipex *pipex, char *argv)
{
	int	fd;

	fd = open(argv, O_WRONLY | O_CLOEXEC | O_CREAT | O_APPEND, \
							S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_OPEN, TYPE_PERROR, true);
	return (fd);
}

static char	*to_empty(char *s)
{
	if (s == NULL)
		return (EMPTY);
	else
		return (s);
}

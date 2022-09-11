/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open_here_doc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:31 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/11 12:50:25 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	create_file_here_doc(t_pipex *pipex);
static void	make_content_here_doc(t_pipex *pipex, char **argv, int fd);

//TODO err
void	open_here_doc(t_pipex *pipex, int argc, char **argv)
{
	size_t	last_index;
	int 	fd;
	
	last_index = argc - 1;
	fd = create_file_here_doc(pipex);
	make_content_here_doc(pipex, argv, fd);
	pipex->file_fd[READ] = open_read_file(pipex, ".here_doc");
	pipex->file_fd[WRITE] = open_write_file(pipex, argv[last_index]);
}

static int	create_file_here_doc(t_pipex *pipex)
{
	int	fd;

	fd = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == ERR_NUM)
		exit_with_error(pipex, ERR_MSG_OPEN, 1);
	return (fd);
}

static char *to_empty(char *s)
{
    if (s == NULL)
        return ("");
    else
        return (s);
}

static void	make_content_here_doc(t_pipex *pipex, char **argv, int fd)
{
	char	*line;
	char 	*content;
	char	*temp;
	char	*limiter;
	
	content = NULL;
	limiter = x_strjoin(pipex, to_empty(argv[2]), "\n");
   	while (1)
   	{
		ft_putstr_fd("pipe heredoc> ", 1);
   	    line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(line)) == SAME_STRING)
		{
	   	 	free(line);
			break;
		}
		temp = content;
		content = x_strjoin(pipex, to_empty(content), to_empty(line));
   		free(temp);
		free(line);
   	}
	ft_putstr_fd(content, fd);
	free(content);
	free(limiter);
	x_close(pipex, fd);
}

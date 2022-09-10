/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:31 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/10 23:40:28 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_read_file(t_pipex *pipex ,char *argv);
static int	open_write_file(t_pipex *pipex, char *argv);

//TODO err
void	open_case_here_doc(t_pipex *pipex, int argc, char **argv)
{
	size_t	last_index;
	char	*word;
	char 	*str;
	int 	fd;
	char *temp;
	
	last_index = argc - 1;
	pipex->file_fd[READ] = STDIN_FILENO;
	fd = dup(pipex->file_fd[READ]);
	pipex->file_fd[WRITE] = open_write_file(pipex, argv[last_index]);

	str = "";
   	while (1)
   	{
		ft_putstr_fd("pipe heredoc> ", 1);
   	    word = get_next_line(STDIN_FILENO);
		temp = str;
		if (ft_strncmp(word, argv[2], ft_strlen(word) - 1) == SAME_STRING)
		{
   	    	free(temp);
			break;
		}
		str = x_strjoin(pipex, str, word);
   	    //free(temp);
		free(word);
   	}
	ft_putstr_fd(str, fd);
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

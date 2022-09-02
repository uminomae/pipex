/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:04:46 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/03 02:08:20 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>

// temp_devided_list : path line of env by split() 
// list_of_directry : add slash
// virtual_argv : argv for execve()
// list_absolute_path_of_command : fullpath including basename
typedef struct s_v_argv
{
	char	**temp_devided_list;
	char	**list_of_directry;
	char	**virtual_argv;
	char	**list_absolute_path_of_command;
	char	*command_name;
}	t_v_argv;

// pid : process ID
// env : same as printenv
// pipe_fd : arg of pipe() 
// file_fd : for open(), write()
typedef struct s_pipex
{
	pid_t			pid[2];
	char			**argv;
	char			**env;
	int				pipe_fd[2];
	int				file_fd[2];
	struct s_v_argv	v_argv;
}	t_pipex;

# define READ 0
# define WRITE 1

// <fcntl.h>
///* open-only flags */
//#define O_RDONLY        0x0000          /* open for reading only */
//#define O_WRONLY        0x0001          /* open for writing only */
//#define O_CLOEXEC       0x1000000       /* implicitly set FD_CLOEXEC */
//#define O_CREAT         0x0200          /* create if nonexistant */
//#define O_TRUNC         0x0400          /* truncate to zero length */
///* File mode */
///* Read, write, execute/search by owner */
//#define S_IRUSR         0000400         /* [XSI] R for owner */
//#define S_IWUSR         0000200         /* [XSI] W for owner */
///* Read, write, execute/search by group */
//#define S_IRGRP         0000040         /* [XSI] R for group */
///* Read, write, execute/search by others */
//#define S_IROTH         0000004         /* [XSI] R for other */

//begin
void	validate_number_of_arguments(int argc);
void	init_struct(t_pipex *pipex, char **argv, char **env);
//close
void	close_unused_file_descriptor(t_v_argv *v_argv, int fd);
void	close_both_pipe(t_v_argv *v_argv, int *pipe_fd);
//exit
void	exit_successfully(t_v_argv *v_argv);
void	exit_with_error(t_v_argv *v_argv, char *str);

// free
void	safe_free(char **malloc_ptr);
void	free_list_absolute_path_of_command(t_v_argv *v);
void	free_virtual_argv(t_v_argv *v);
void	free_list_of_directry(t_v_argv *v);
void	free_temp_devided_list(t_v_argv *v);
//run
pid_t	create_child_process_by_fork_func(t_pipex *pipex);
void	open_files_on_purpose(t_v_argv *v_argv, char *const *argv, int *fd, int in_out);
//void	duplicate_to_standard_in_out(\
			//t_pipex *pipex, int file_for_reading, int file_for_writing);
void	duplicate_to_standard_in_out(t_v_argv *v_argv, \
							int file_for_reading, int file_for_writing);
void	wait_pid_for_child_process(t_v_argv *v_argv, pid_t process_id);
//exe get path
size_t	get_path_line_from_env(t_pipex *pipex);
char	**split_list_of_directry_from_path_line(\
			t_pipex *pipex, size_t path_index);
char	**join_slash_path_of_directry(t_pipex *pipex, char **list_of_directry);
size_t	scale_list_including_null(char **list);
//exe make v_argv
char	**split_virtual_argv_from_real_argv(\
			t_pipex *pipex, char *command_from_argv);
char	**join_file_and_directry_name_to_get_absolute_path(\
			t_pipex *pipex, char **list_of_directry, char *command_name);
int		get_index_accessible_path(char **list_absolute_path_of_command);
char	**switch_first_argv_to_absolute_path(\
			t_pipex *pipex, t_v_argv *v, size_t index);
//execute
void	execute_command(t_pipex *pipex, char *argv);

#endif

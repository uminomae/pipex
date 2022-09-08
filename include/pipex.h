/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:04:46 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/08 15:33:10 by hioikawa         ###   ########.fr       */
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
}	t_v_argv;

typedef struct s_pipe_node
{
	int					pipe_fd[2];
	struct s_pipe_node	*prev;	
	struct s_pipe_node	*next;
	pid_t				process_id;
}	t_pipe_node;

typedef struct s_pipe_list
{
	struct s_pipe_node	*head;
	struct s_pipe_node	*tail;
}	t_pipe_list;

// pid : process ID
// env : same as printenv
// pipe_list : arg of pipe() 
// file_fd : for open(), write()
typedef struct s_pipex
{
	pid_t			pid[2];
	int				argc;
	char			**argv;
	char			**env;
	//int				pipe_list[2];
	struct s_pipe_list	pipe_list;
	int				file_fd[2];
	struct s_v_argv	v_argv;
	size_t			pipe_n;
}	t_pipex;

# define ERR_NUM			-1
# define READ 				0
# define WRITE				1

# define GROUP_OF_CALLER	0
# define CHILD_PROCESS		0
# define ABS_PATH_CMD		0
# define FIRST_LINE			0
# define SAME_STRING		0
# define NOT_FIND			0

# define FILE_FOR_READ		1
# define FIRST_CMD			2
# define LAST_COMMAND		3

# define NUM_OF_BASE		5

# define ONE_BECAUSE_IDX_FROM_0		1

# define CHAR_COLON			':'

# define STR_SLASH			"/"
# define WORD_FIND_PATH		"PATH="
# define ERR_MSG_VALID		"error : 5 arguments are required"
# define ERR_MSG_PIPE		"pipe()"
# define ERR_MSG_CLOSE		"close()"
# define ERR_MSG_FORK		"fork()"
# define ERR_MSG_WAITPID	"waitpid()"
# define ERR_MSG_EXCECVE	"execve()"
# define ERR_MSG_DUP2		"dup2()"
# define ERR_MSG_ACCESS		"access()"
# define ERR_MSG_OPEN		"open()"
# define ERR_MSG_NO_CMD		"error : no command()"
# define ERR_MSG_STRDUP		"ft_strdup()"
# define ERR_MSG_SPLIT		"ft_split()"
# define ERR_MSG_MALLOC		"malloc()"
# define ERR_MSG_STRJOIN	"ft_strjoin()"

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

void	x_pipe(int *pipe_fd, t_v_argv *v_argv);
//begin
void	begin_pipex(t_pipex *pipex, int argc, char **argv, char **env);
//close end
void	close_both_pipe(t_v_argv *v_argv, const int *const pipe_fd);
void	x_close(t_v_argv *v_argv, int fd);
void	safe_free(char **malloc_ptr);
void	exit_successfully(t_v_argv *v_argv);
void	exit_with_error(t_v_argv *v_argv, char *str);
//free struct
void	free_struct(t_v_argv *v_argv);
//run
//void	run_child_to_file(\
//				t_pipex *pipex, char **argv, int read_or_write, int argv_idx);
pid_t	run_child_to_file(\
				t_pipex *pipex, char **argv, int read_or_write, int argv_idx);
//size_t	run_multiple_pipes(t_pipex *pipex, int argc);
size_t	run_multiple_pipes(t_pipex *pipex, size_t num_pipe);

void	x_dup2(t_v_argv *v_argv, int file, int fd);

pid_t	create_child_process_by_fork_func(t_pipex *pipex);
//void	get_virtual_argv(\
//	t_pipex *pipex, int fd_for_read, int fd_for_write, char *command_from_argv);
char	**get_virtual_argv(\
	t_pipex *pipex, char *command_from_argv);

//void	open_files_on_purpose(\
//			t_pipex *pipex, char *const *argv, int *file_fd, int read_or_write);
void	wait_pid_for_child_process(t_v_argv *v_argv, pid_t process_id);
size_t	get_path_line_from_env(char **env, char *str, size_t len);
char	**split_list_of_directry_from_path_line(\
			t_pipex *pipex, size_t path_index);
char	**join_slash_path_of_directry(t_pipex *pipex, char **list_of_directry);
size_t	scale_list_including_null(char **list);
char	**split_virtual_argv_from_real_argv(\
			t_pipex *pipex, char *command_from_argv);
char	**join_file_and_directry_name_to_get_absolute_path(\
			t_pipex *pipex, char **list_of_directry, char *command_name);
int		get_index_accessible_path(char **list_absolute_path_of_command);
char	**switch_first_argv_to_absolute_path(\
			t_pipex *pipex, t_v_argv *v, size_t index);
//util
char	**split_str_and_check_for_null(\
							t_v_argv *v_argv, char *str, char delimiter);
void	*malloc_and_check_for_null(t_v_argv *v_argv, size_t size);
char	*join_str_and_check_for_null(\
						t_v_argv *v_argv, char *str, char *str_to_add);
size_t	scale_list_including_null(char **list);

#endif

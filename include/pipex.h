/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:04:46 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/09 09:19:22 by hioikawa         ###   ########.fr       */
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
	//char			**env;
	//int				pipe_list[2];
	struct s_pipe_list	pipe_list;
	int				file_fd[2];
	struct s_v_argv	v_argv;
	size_t			pipe_n;
}	t_pipex;

extern char **environ;

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

# define DELIMITER_PATH		':'
# define DELIMITER_CMD		' '
# define IS_ABS_PATH		'/'

# define STR_SLASH			"/"
# define WORD_FIND_PATH		"PATH="
# define ERR_MSG_ARGC		"error : 5 arguments are required"
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

void	x_pipe(int *pipe_fd, t_v_argv *v_argv);
void	x_dup2(t_v_argv *v_argv, int file, int fd);
void	x_execve(t_pipex *pipex, char **virtual_argv);
size_t	make_pipe(t_pipex *pipex, int argc, size_t argc_of_base);

void	open_files(t_pipex *pipex, char *const *argv, int *file_fd);

//begin
void	begin_pipex(t_pipex *pipex, int argc, char **argv);
//void	begin_pipex(t_pipex *pipex, int argc, char **argv, char **env);
//close end
void	close_both_pipe(t_v_argv *v_argv, const int *const pipe_fd);
void	x_close(t_v_argv *v_argv, int fd);
void	safe_free(char **malloc_ptr);
void	exit_successfully(t_v_argv *v_argv);
void	exit_with_error(t_v_argv *v_argv, char *str);
//free struct
void	free_struct(t_v_argv *v_argv);
//run
pid_t	run_child_to_file(\
				t_pipex *pipex, char **argv, int read_or_write, int argv_idx);
size_t	run_multiple_pipes(t_pipex *pipex, size_t num_pipe);
pid_t	x_fork(t_pipex *pipex);
void	x_waitpid(t_v_argv *v_argv, pid_t process_id);
void	get_path_from_env_and_make_list(t_pipex *pipex, t_v_argv *v);
char	**make_virtual_argv(\
				t_pipex *pipex, t_v_argv *v, char *command_from_argv);
size_t	scale_list_including_null(char **list);
//util
char	**x_split(\
							t_v_argv *v_argv, char *str, char delimiter);
void	*x_malloc(t_v_argv *v_argv, size_t size);
char	*x_strjoin(\
						t_v_argv *v_argv, char *str, char *str_to_add);
size_t	scale_list_including_null(char **list);

#endif

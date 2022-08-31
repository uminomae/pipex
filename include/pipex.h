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
typedef struct	s_v_argv
{
	char	**temp_devided_list;
	char	**list_of_directry;
	char	**virtual_argv;
	char	**list_absolute_path_of_command;
	char	*command_name;
} t_v_argv;

// pid : process ID
// env : same as printenv
// pipe_fd : arg of pipe() 
// file_fd : for open(), write()
typedef struct	s_pipex
{
	pid_t			pid[2];
	int				argc;
	char			**argv;
	char			**env;
	int				pipe_fd[2];
	int				file_fd[2];
	struct s_v_argv	v_argv;
} t_pipex;

# define READ 0
# define WRITE 1
# define STANDARD_INPUT 0
# define STANDARD_OUTPUT 1

/*
 * File status flags: these are used by open(2), fcntl(2).
 * They are also used (indirectly) in the kernel file structure f_flags,
 * which is a superset of the open/fcntl flags.  Open flags and f_flags
 * are inter-convertible using OFLAGS(fflags) and FFLAGS(oflags).
 * Open/fcntl flags begin with O_; kernel-internal flags begin with F.
 */
/* open-only flags */
//#define O_RDONLY        0x0000          /* open for reading only */
//S_IRUSR	00400：所有者（owner）による読み取り（read）。
//S_IWUSR	00200：所有者による書き込み（write）。
//S_IRGRP	00040：グループ（group）による読み取り。
//S_IROTH	00004：他人（others）による読み取り。

//main
void	begin_pipex(t_pipex *pipex,int argc, char **argv, char **env);
void	create_pipe_fd(t_pipex *pipex);
void	run_read_side(t_pipex *pipex, int i);
void	run_write_side(t_pipex *pipex, int i);
//begin
void	check_for_valid_value(int argc);
void	init_struct(t_pipex *pipex,int argc, char **argv, char **env);
//close
int		close_unused_file_descriptor(t_pipex *pipex, int fd);
void	close_both_pipe(t_pipex *pipex);
//exit
void	exit_successfully_child_process(t_pipex *pipex);
void	exit_with_error_child_process(t_pipex *pipex, char *str);
// free
void	set_free_together(t_pipex *pipex);
void	safe_free(char **malloc_ptr);
void	free_list_absolute_path_of_command(t_v_argv *v);
void	free_virtual_argv(t_v_argv *v);
void	free_list_of_directry(t_v_argv *v);
void	free_temp_devided_list(t_v_argv *v);
//run
void	create_child_process_by_fork_func(t_pipex *pipex, int i);
void	open_file(t_pipex *pipex, int in_out);
void	duplicate_to_standard_in_out(t_pipex *pipex, int file_for_reading, int file_for_writing);
void	wait_pid_for_child_process(t_pipex *pipex, int i);
//get path
size_t	get_path_line_from_env(t_pipex *pipex);
char	**split_list_of_directry_from_path_line(t_pipex *pipex, size_t path_index);
char	**join_slash_path_of_directry(t_pipex *pipex, char **list_of_directry);
size_t	count_pointer_including_null(char **list);
//make v_argv
char	**split_virtual_argv_from_real_argv(t_pipex *pipex, char *command_from_argv);
char	**join_file_and_directry_name_to_get_absolute_path(t_pipex *pipex, char **list_of_directry, char *command_name);
size_t	get_index_accessible_path(t_pipex *pipex, char **list_absolute_path_of_command);
char	**switch_first_argv_to_absolute_path(t_pipex *pipex, t_v_argv *v, size_t index);
//execute
void	get_path_from_env_and_make_list(t_pipex *pipex, t_v_argv *v);
char	**make_virtual_argv(t_pipex *pipex, t_v_argv *v, char *command_from_argv);
void	execute_command(t_pipex *pipex, char *argv);



#endif

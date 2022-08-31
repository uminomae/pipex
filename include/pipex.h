#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>


typedef struct	s_v_argv
{
	char	**temp_devided_list;
	char	**list_of_directry;
	char	**virtual_argv;
	char	**list_absolute_path_of_command;
} t_v_argv;


typedef struct	s_pipex
{
	pid_t			pid[2];
	int				argc;
	char			**argv;
	char			**env;
	int				pipe_fd[2];
	int				file_fd[2];
	//char	**virtual_argv;
	struct s_v_argv	v_argv;
} t_pipex;

# define ERR_CODE_1 1
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

//begin()
void	create_pipe_fd(t_pipex *pipex);
void	init_struct(t_pipex *pipex,int argc, char **argv, char **env);
void	check_for_valid_value(int argc);
void	begin_pipex(t_pipex *pipex,int argc, char **argv, char **env);
//
//void	exit_with_error(char *str);
void	exit_with_error(t_pipex *pipex, char *str);
//int		close_file_descriptor(int fd);
int		close_file_descriptor(t_pipex *pipex, int fd);
//void	close_pipe_and_exit_with_error(t_pipex *pipex, char *str);
void	close_both_pipe(t_pipex *pipex);
void	safe_free(char **malloc_ptr);
size_t	count_pointer(char **list);
//
void	create_child_process(t_pipex *pipex, int i);
void	open_file(t_pipex *pipex, int in_out);
void	duplicate_to_standard_in_out(t_pipex *pipex, int file_for_reading, int file_for_writing);
//
void	wait_for_child_process(t_pipex *pipex, int i);
//
size_t	get_path_line_from_env(t_pipex *pipex);
char	**split_list_of_directry_from_path_line(t_pipex *pipex, size_t path_index);
char	**make_complete_path_of_directory(char **list_of_directry);
char	**make_virtual_argv_from_real_argv(t_pipex *pipex, char *command_from_argv);
char	**make_absolute_path_of_command(char **list_of_directry_full, char *command_name);
char	**get_virtual_argv(t_pipex *pipex, char *command_from_argv);
size_t	get_index_accessible_path(t_pipex *pipex, char **list_absolute_path_of_command);
//
void	execute_command_read(t_pipex *pipex);
void	execute_command_write(t_pipex *pipex);
//
void	begin_pipex(t_pipex *pipex,int argc, char **argv, char **env);
void	run_read_side(t_pipex *pipex, int i);
void	run_write_side(t_pipex *pipex, int i);
void	run_child_process(t_pipex *pipex, int i, int read_fd, int out_fd);
//
void	free_list_absolute_path_of_command(t_v_argv *v);
void	free_virtual_argv(t_v_argv *v);
void	free_list_of_directry(t_v_argv *v);
void	free_temp_devided_list(t_v_argv *v);


#endif

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>

typedef struct	s_pipex
{
	pid_t	pid[2];
	int		argc;
	char	**argv;
	char	**env;
	int		pipe_fd[2];
	int		file_fd[2];
} t_pipex;

# define ERR_CODE_1 1
# define READ 0
# define WRITE 1
# define STANDARD_INPUT 0
# define STANDARD_OUTPUT 1

//# define GET_AVG_READ	char *argv1_test[3];\
//	argv1_test[0] = "/usr/bin/grep";\
//	argv1_test[1] = "a1";\
//	argv1_test[2] = NULL;\

//# define GET_AVG_WRITE	char *argv1_test[3];\
//	argv1_test[0] = "/bin/cat";\
//	argv1_test[1] = NULL;\
//	argv1_test[2] = NULL;\

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
void	exit_with_error(char *str);
int		close_file_descriptor(int fd);
void	close_pipe_and_exit_with_error(t_pipex *pipex, char *str);
//
void	create_child_process(t_pipex *pipex, int i);
void	open_file(t_pipex *pipex, int in_out);
void	duplicate_to_standard_in_out(int old_in_fd, int old_out_fd);
//
void	wait_for_child_process(t_pipex *pipex, int i);
//
size_t	get_path_line_from_env(t_pipex *pipex);
char	**get_list_of_directry_from_path_line(t_pipex *pipex, size_t path_index);
char	**make_virtual_argv_from_real_argv(char *command_from_argv);
char	*make_absolute_path(char **list_of_directry, char *command_name);
char	**get_virtual_argv(t_pipex *pipex, char *command_from_argv);
//
void	execute_command_read(t_pipex *pipex);
void	execute_command_write(t_pipex *pipex);
//
void	begin_pipex(t_pipex *pipex,int argc, char **argv, char **env);
void	run_read_side(t_pipex *pipex, int i);
void	run_write_side(t_pipex *pipex, int i);
void	run_child_process(t_pipex *pipex, int i, int read_fd, int out_fd);

#endif

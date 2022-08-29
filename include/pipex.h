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
	//int		file_fd[2];

	int		status[2];
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
void	exit_with_error(char *str);
void	create_child_process(t_pipex *pipex, int i);
void	wait_for_child_process(t_pipex *pipex, int i);
//
void	run_read_side_child_process(t_pipex *pipex);
void	run_write_side_child_process(t_pipex *pipex);
//void	parent_process(t_pipex *pipex);

#endif

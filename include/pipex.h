#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>

typedef struct	s_pipex
{
	pid_t	pid;
	int		argc;
	char	**argv;
	char	**env;
	int		pipe_fd[2];
	int		file_fd[2];
	int		status;
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

//void	run_pipe(char **argv, char **env, t_pipex *pipex);
void	child_process(char **argv, char **env, int *pipe_fd);
void	parent_process(char **argv, char **env, int *pipe_fd);

#endif

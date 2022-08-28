#include "pipex.h"

void	exit_with_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	check_for_valid_value(int argc)
{
	if (argc == 5)
		return ;
	else
		exit_with_error();
}

void	init_struct(t_pipex *pipex,int argc, char **argv, char **env)
{
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->env = env;
}

void	create_child_process(t_pipex *pipex)
{
	int status;

	status = pipe(pipex->pipe_fd);
	if (status == -1)
		exit_with_error("pipe");
	pipex->pid = fork();
	if (pipex->pid == -1)
		exit_with_error("fork");
}

void run_pipe(char **argv, char **env, t_pipex *pipex)
{
	if (pipex->pid == 0)
		child_process(argv, env, pipex->pipe_fd);
	waitpid(pipex->pid, NULL, 0);
	parent_process(argv, env, pipex->pipe_fd);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex pipex;

	check_for_valid_value(argc);
	init_struct(&pipex, argc, argv, env);
	create_child_process(&pipex);
	run_pipe(argv, env, &pipex);

	//(void)argv;
	//(void)argc;
	//(void)env;
}


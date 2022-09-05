/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/05 11:36:43 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//./pipex here_doc LIMITER "cat" "grep a" test/outfile191

void	read_heredoc(t_pipex *pipex)
{
	char	buf[1024];
	int		len;

	while (1)
	{
		len = read(0, buf, 1);
		if (len == -1)
			exit_with_error(&pipex->v_argv, "read()");
		//TODO
		//if (ft_strncmp(buf, "LIMITER", ft_strlen("LIMITER")) == 0)
		if (ft_strncmp(buf, "LIMITER", 7) == 0)
			return ;
		//write(pipex->pipe_fd[WRITE], buf, ft_strlen(buf));
		write(1, buf, ft_strlen(buf));
	}
}


static void	get_path_from_env_and_make_list2(t_pipex *pipex, t_v_argv *v)
{
	size_t		path_line;

	path_line = get_path_line_from_env(\
					pipex->env, WORD_FIND_PATH, ft_strlen(WORD_FIND_PATH));
	v->temp_devided_list = \
					split_list_of_directry_from_path_line(pipex, path_line);
	v->list_of_directry = \
					join_slash_path_of_directry(pipex, v->temp_devided_list);
}

static char	**make_virtual_argv2(\
				t_pipex *pipex, t_v_argv *v, char *command_from_argv)
{
	int	index;

	v->virtual_argv = \
			split_virtual_argv_from_real_argv(pipex, command_from_argv);
	v->list_absolute_path_of_command = \
					join_file_and_directry_name_to_get_absolute_path(\
						pipex, v->list_of_directry, v->virtual_argv[0]);
	index = get_index_accessible_path(v->list_absolute_path_of_command);
	if (index == ERR_NUM)
		exit_with_error(&pipex->v_argv, ERR_MSG_ACCESS);
	v->virtual_argv = switch_first_argv_to_absolute_path(pipex, v, index);
	return (v->virtual_argv);
}

void	dup_and_exe_heredoc(t_pipex *pipex, char *command_from_argv)
{
	char		**virtual_argv;
	int			ret;

	get_path_from_env_and_make_list2(pipex, &pipex->v_argv);
	virtual_argv = make_virtual_argv2(pipex, &pipex->v_argv, command_from_argv);
	ret = execve(virtual_argv[ABS_PATH_CMD], virtual_argv, pipex->env);
	if (ret == ERR_NUM)
		exit_with_error(&pipex->v_argv, ERR_MSG_EXCECVE);
}

//./pipex here_doc LIMITER "cat" "grep a" test/outfile21
void	run_child_heredoc(\
	t_pipex *pipex, char **argv, int read_or_write, int argv_idx)
{
	const int *const	pipe = pipex->pipe_fd;
	int *const			file_fd = pipex->file_fd;
	t_v_argv			*v_argv;
	pid_t				process_id;

	v_argv = &pipex->v_argv;
	process_id = create_child_process_by_fork_func(pipex);
	if (process_id == CHILD_PROCESS)
	{
		close_unused_file_descriptor(v_argv, pipe[read_or_write]);
		if (read_or_write == READ)
		{
			read_heredoc(pipex);
			dup_and_exe_heredoc(pipex, argv[argv_idx]);
		}
		else if (read_or_write == WRITE)
		{
			open_files_on_purpose(pipex, argv, file_fd, read_or_write);
			duplicate_and_execute(\
				pipex, pipe[READ], file_fd[WRITE], argv[argv_idx]);
		}
		close_unused_file_descriptor(v_argv, file_fd[read_or_write]);
		exit_successfully(v_argv);
	}
	if (read_or_write == WRITE)
		close_both_pipe(v_argv, pipe);
	wait_pid_for_child_process(v_argv, process_id);
}



void	run_heredoc(t_pipex *pipex, char **argv)
{
	//make argv
	//TODO 3 define
	printf("here1\n");
	run_child_heredoc(pipex, argv, READ, 3);
	printf("aaaaaaa\n");
	run_child_heredoc(pipex, argv, WRITE, 4);
	printf("bbbbbbb\n");
}

// TODO t_v_argvでいいのか？ パスの材料とパスと仮想argv
int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	size_t	add_pipes;

	begin_pipex(&pipex, argc, argv, env);
	printf("bccc\n");
	if (pipex.here_doc_flag == true)
		run_heredoc(&pipex, argv);
	else
	{
			printf("dd22\n");


		

		run_child_to_file(&pipex, argv, READ, FIRST_CMD);
		add_pipes = run_multiple_pipes(&pipex, argc);
		run_child_to_file(&pipex, argv, WRITE, add_pipes + LAST_COMMAND);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/04 22:15:02 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TODO t_v_argvでいいのか？ パスの材料とパスと仮想argv
int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	size_t	add_pipes;

	begin_pipex(&pipex, argc, argv, env);
	run_child_to_file(&pipex, argv, READ, FIRST_CMD	);
	add_pipes = run_multiple_pipes(&pipex, argc);
	run_child_to_file(&pipex, argv, WRITE, add_pipes + LAST_COMMAND);
	return (0);
}

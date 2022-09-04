/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa <hioikawa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:51:27 by hioikawa          #+#    #+#             */
/*   Updated: 2022/09/04 13:40:46 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	size_t	i;
	
	begin_pipex(&pipex, argc, argv, env);
	run_child_to_file(&pipex, argv, READ, 2);
	i = run_multiple_pipes(&pipex, argc, argv);
	run_child_to_file(&pipex, argv, WRITE, i + 3);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa </var/mail/hioikawa>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:30:56 by hioikawa          #+#    #+#             */
/*   Updated: 2022/02/25 16:29:52 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len_s;

	if (s == NULL)
		return ;
	len_s = ft_strlen(s);
	write(fd, s, len_s);
}
/*
int main()
{
	size_t n = UINT_MAX;
	n += 10;
	char *s = malloc(sizeof(char) * (n + 1));

	ft_putstr_fd("abc\n", 1);
	ft_putstr_fd(NULL, 1);
	ft_putstr_fd("cba\n", 1);
	memset(s, 'a', UINT_MAX + 5);
	ft_putstr_fd(s, 1);
}
*/

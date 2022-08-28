/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa </var/mail/hioikawa>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:30:22 by hioikawa          #+#    #+#             */
/*   Updated: 2022/02/23 07:08:19 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = n * (-1);
	}
	if (0 <= n && n <= 9)
		ft_putchar_fd(n + '0', fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
/*
int main(int argc, char *argv[])
{
	puts("");ft_putnbr_fd(-1, 1);
	puts("");ft_putnbr_fd(-0, 1);
	puts("");ft_putnbr_fd(INT_MAX, 1);
	puts("");ft_putnbr_fd(INT_MIN, 1);
	puts("");ft_putnbr_fd(UINT_MAX, 1);puts("");
	puts("---argv---");
	if (argc == 2)
		ft_putnbr_fd(atoi(argv[1]), 1);puts("");
	return (0);
}
*/

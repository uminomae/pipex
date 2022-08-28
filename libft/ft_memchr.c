/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa </var/mail/hioikawa>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:23:47 by hioikawa          #+#    #+#             */
/*   Updated: 2022/03/02 16:57:57 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ucp_s;
	unsigned char	uc_c;
	size_t			i;

	ucp_s = (unsigned char *)s;
	uc_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (ucp_s[i] == uc_c)
			return ((void *)&ucp_s[i]);
		i++;
	}
	return (NULL);
}
/*
int main()
{
	char    s1[30] = "abcdfecdefghijklmn";
	int     c = 'g';

	printf("%s\n",    memchr(s1, c, 20));
	printf("%s\n", ft_memchr(s1, c, 20));
}
*/

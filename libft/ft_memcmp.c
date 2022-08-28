/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa </var/mail/hioikawa>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:24:12 by hioikawa          #+#    #+#             */
/*   Updated: 2022/02/25 21:19:20 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ucp_s1;
	const unsigned char	*ucp_s2;
	size_t				i;
	int					int_ret;

	ucp_s1 = (const unsigned char *)s1;
	ucp_s2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		int_ret = (int)(ucp_s1[i] - ucp_s2[i]);
		if (int_ret != 0)
			return (int_ret);
		i++;
	}
	return (0);
}

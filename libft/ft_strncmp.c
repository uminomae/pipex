/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa </var/mail/hioikawa>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 04:02:08 by hioikawa          #+#    #+#             */
/*   Updated: 2022/02/05 21:51:28 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*uc_s1;
	unsigned char	*uc_s2;
	size_t			i;
	int				int_ret;

	uc_s1 = (unsigned char *)s1;
	uc_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (uc_s1[i] != '\0' && uc_s2[i] != '\0' && i < n)
	{
		if (uc_s1[i] != uc_s2[i])
		{
			int_ret = (int)(uc_s1[i] - uc_s2[i]);
			return (int_ret);
		}
		i++;
	}
	if (i != n)
	{
		int_ret = (int)(uc_s1[i] - uc_s2[i]);
		return (int_ret);
	}
	return (0);
}

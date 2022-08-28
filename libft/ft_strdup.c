/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa </var/mail/hioikawa>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 03:51:23 by hioikawa          #+#    #+#             */
/*   Updated: 2022/02/25 16:14:34 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*p_cpy;
	size_t	len_src;

	if (src == NULL)
		return (NULL);
	len_src = ft_strlen(src);
	p_cpy = (char *) malloc(sizeof(char) * (len_src + 1));
	if (p_cpy == NULL)
		return (NULL);
	ft_strlcpy(p_cpy, src, len_src + 1);
	return (p_cpy);
}

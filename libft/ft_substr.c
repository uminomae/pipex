/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa </var/mail/hioikawa>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 04:08:04 by hioikawa          #+#    #+#             */
/*   Updated: 2022/02/21 11:19:40 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen_s(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (len < maxlen && s[len] != '\0')
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p_cpy;
	size_t	m_size;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	m_size = ft_strnlen_s(s + start, len);
	p_cpy = (char *) malloc(sizeof(char) * (m_size + 1));
	if (p_cpy == NULL)
		return (NULL);
	ft_strlcpy(p_cpy, s + start, m_size + 1);
	return (p_cpy);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa </var/mail/hioikawa>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:38:08 by hioikawa          #+#    #+#             */
/*   Updated: 2022/03/01 05:08:44 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc_c;
	size_t			i;

	uc_c = (unsigned char)c;
	if (s == NULL)
		return (NULL);
	if (uc_c == '\0')
		return ((char *)s + ft_strlen(s));
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == uc_c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
/*
int main()
{
	char    s1[30] = "abcdfecdefghijklmn";
	int     c = '\0';

	printf("%p\t%p\n", s1,   strchr(s1, c));
	printf("%p\t%p\n", s1,ft_strchr(s1, c));
	c = 'g';
	printf("%s\n",    strchr(s1, c));
	printf("%s\n", ft_strchr(s1, c));
}
*/

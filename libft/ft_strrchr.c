/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa </var/mail/hioikawa>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 04:04:44 by hioikawa          #+#    #+#             */
/*   Updated: 2022/03/01 05:07:48 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	uc_c;
	size_t			i;
	size_t			j;
	size_t			len;

	uc_c = (unsigned char)c;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	if (uc_c == '\0')
		return ((char *)s + len);
	i = 0;
	j = len - 1 ;
	while (i < len)
	{
		if (s[j] == uc_c)
			return ((char *)&s[j]);
		j--;
		i++;
	}
	return (NULL);
}
/*
   int main()
   {
   char    s1[30] = "abcdfeacdaefghiajklmn";
   int     c = '\0';

   printf("%p\t%p\n", s1,   strrchr(s1, c));
   printf("%p\t%p\n", s1,ft_strrchr(s1, c));
   c = 'g';
   printf("%s\n",    strrchr(s1, c));
   printf("%s\n", ft_strrchr(s1, c));
   c = 'a';
   printf("%s\n",    strrchr(s1, c));
   printf("%s\n", ft_strrchr(s1, c));
   }
*/

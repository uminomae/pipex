/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa </var/mail/hioikawa>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 04:02:47 by hioikawa          #+#    #+#             */
/*   Updated: 2022/02/21 09:59:29 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len_ndl;

	if (haystack == NULL)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	len_ndl = ft_strlen(needle);
	if (len < len_ndl)
		return (NULL);
	i = 0;
	while (i < len && haystack[i] != '\0')
	{
		if (len - i >= len_ndl && ft_strncmp(&haystack[i], \
					needle, len_ndl) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
/*
   int main()
   {
   char s[30] = "abbbaabaaabbb";

   ft_strnstr(NULL,"\0",1);
   ft_strnstr("\0", "\0", 1);
   ft_strnstr(NULL, "aaa", 0);
   ft_strnstr("\0", "aaa", -1);
   printf("%s",ft_strnstr(s, "aaa", 20));
   return(0);
   }
   */

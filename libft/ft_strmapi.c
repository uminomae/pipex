/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa </var/mail/hioikawa>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 04:01:32 by hioikawa          #+#    #+#             */
/*   Updated: 2022/03/02 16:34:07 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*cpy_s;

	if (s == NULL || f == NULL)
		return (NULL);
	cpy_s = ft_strdup(s);
	if (cpy_s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		cpy_s[i] = (*f)((unsigned int)i, s[i]);
		i++;
	}
	cpy_s[i] = '\0';
	return (cpy_s);
}
/*
char    ft_mapi_isalnum(int c)


	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z' ) || \
			('0' <= c && c <= '9'))
		return ('1');
	return ('0');
}

char    func(unsigned int i, char j)
{
	char    c;

	(void)i;
	c = toupper(j);
	return (c);
}

char    func2(unsigned int i, char j)
{
	char    c;

	(void)i;
	c = tolower(j);
	return (c);
}

char    func3(unsigned int i, char j)
{
	char    c;

	(void)i;
	c = ft_mapi_isalnum(j);
	return (c);
}

int    test_strmapi(char *s1, char *s2, char *s3)
{
	printf("%s - > %s (%s)\n", s1, s2, s3);
	return (0);
}

int    main()
{
	char    *s;

	s = strdup("abC-e");
	test_strmapi(s,ft_strmapi(s, func),"to_upper");
	test_strmapi(s,ft_strmapi(s, func2),"to_lower");
	test_strmapi(s,ft_strmapi(s, func3),"to_alnum");
	test_strmapi(NULL,ft_strmapi(s, func3),"s = NULL");
	test_strmapi(s,NULL,"f = NULL");
	test_strmapi(NULL,NULL,"NULL & NULL");
}
*/

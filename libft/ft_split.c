/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa </var/mail/hioikawa>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:31:49 by hioikawa          #+#    #+#             */
/*   Updated: 2022/03/01 05:34:26 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	safe_free(char **malloc_pp)
{
	free(*malloc_pp);
	*malloc_pp = NULL;
}

static void	malloc_free(char **ret_pp)
{
	size_t	i;

	i = 0;
	while (ret_pp[i] != NULL)
	{
		safe_free(&ret_pp[i]);
		i++;
	}
	safe_free(&ret_pp[i]);
	free(ret_pp);
	ret_pp = NULL;
}

static char	**split_cpy(char **ret_pp, char *cpy_s, size_t num_of_str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < num_of_str)
	{
		while (cpy_s[j] == '\0')
			j++;
		ret_pp[i] = ft_strdup(&cpy_s[j]);
		if (ret_pp[i] == NULL)
		{
			malloc_free(ret_pp);
			return (NULL);
		}
		j += ft_strlen(&cpy_s[j]);
		i++;
	}
	ret_pp[num_of_str] = NULL;
	return (ret_pp);
}

static size_t	count_and_conversion_zero(char *cpy_s, char c)
{
	size_t	i;
	size_t	num_of_str;

	i = 0;
	num_of_str = 0;
	while (cpy_s[i] != '\0')
	{
		while (cpy_s[i] == c && cpy_s[i] != '\0')
		{
			cpy_s[i] = '\0';
			i++;
		}
		if (cpy_s[i] != c && cpy_s[i] != '\0')
			num_of_str++;
		while (cpy_s[i] != c && cpy_s[i] != '\0')
			i++;
	}
	return (num_of_str);
}

char	**ft_split(char const *s, char c)
{
	char	**ret_pp;
	char	*cpy_s;
	size_t	num_of_str;

	if (s == NULL)
		return (NULL);
	cpy_s = ft_strdup(s);
	if (cpy_s == NULL)
		return (NULL);
	num_of_str = count_and_conversion_zero(cpy_s, c);
	ret_pp = (char **)malloc(sizeof(char *) * (num_of_str + 1));
	if (ret_pp == NULL)
	{
		safe_free(&cpy_s);
		return (NULL);
	}
	ret_pp = split_cpy(ret_pp, cpy_s, num_of_str);
	safe_free(&cpy_s);
	return (ret_pp);
}
/*
int main()
{
	size_t j = 0;
	char	**s;
	char    str[100] ="      split       this for   me  !       ";
	char    c = ' ';

	s = ft_split(str,c);
	if (s != NULL)
	{
		while(s[j] != NULL)
		{
			printf("\x1b[31m""%d\t%p\tc=%s\n", __LINE__, s[j], s[j]);
			j++;
		}
	}
	if (s!= NULL)
		printf("\x1b[36m""%d\t%p\tc=%s\n", __LINE__, s[j], s[j]);
	else
		printf("s = %p", s);
	puts("\x1b[35m");
	system("leaks -q a.out");
	puts("\x1b[37m");
}
*/

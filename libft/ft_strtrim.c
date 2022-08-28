/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa </var/mail/hioikawa>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 04:05:55 by hioikawa          #+#    #+#             */
/*   Updated: 2022/03/02 16:51:10 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_set(const char *set, unsigned char s1_i)
{
	size_t	k;

	k = 0;
	while (k < ft_strlen(set))
	{
		if (set[k] == s1_i)
			return (1);
		k++;
	}
	return (0);
}

static size_t	ft_count_del_r(char const *s1, char const *set, size_t len_s1)
{
	size_t	num_r;

	num_r = 0;
	while (num_r < len_s1)
	{
		if (ft_is_set(set, s1[len_s1 - num_r - 1]) == 0)
			break ;
		num_r++;
	}
	return (num_r);
}

static size_t	ft_count_del(char const *s1, char const *set, size_t len_s1)
{
	size_t	num;

	num = 0;
	while (num < len_s1)
	{
		if (ft_is_set(set, s1[num]) == 0)
			break ;
		num++;
	}
	return (num);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len_s1;
	size_t	trim_len;
	size_t	trim_len_r;
	size_t	len_cpy;
	char	*p_cpy;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_strdup(""));
	len_s1 = ft_strlen(s1);
	trim_len = ft_count_del(s1, set, len_s1);
	trim_len_r = ft_count_del_r(s1, set, len_s1);
	len_cpy = len_s1 - trim_len - trim_len_r;
	if (trim_len == len_s1)
		return (ft_strdup(""));
	p_cpy = ft_substr(&s1[trim_len], 0, len_cpy);
	return (p_cpy);
}
/*
int main()
{
   char    *ft_ret;

   printf("%s\n", ft_strtrim("123456a7890", "1234567890"));
   printf("%s\n", ft_strtrim("baaabbaab", "b"));
   printf("%s\n", ft_strtrim("b\\0cbbbcbbbb\\0\\0a", "ba\\0b"));
   printf("%s\n", ft_strtrim("bbb", "b"));
   return (0);
}
*/

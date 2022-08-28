/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa </var/mail/hioikawa>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 03:52:13 by hioikawa          #+#    #+#             */
/*   Updated: 2022/02/25 16:22:30 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	len_s;
	size_t	i;

	if (s == NULL || f == NULL)
		return ;
	len_s = ft_strlen(s);
	i = 0;
	while (i < len_s)
	{
		(*f)(i, s + i);
		i++;
	}
}
/*
   static void    ft_putchar(unsigned int i, char *s)
   {
   (void) i;
   write(1, s, 1);
   }

   static void    ft_putendl(unsigned int i, char *s)
   {
   (void) i;
   write(1, s, 1);
   write(1, "\n", 1);
   }

   int main()
   {
   ft_striteri("12345\n", ft_putchar);
   ft_striteri("12345\n", ft_putendl);
   ft_striteri(NULL, ft_putchar);
   ft_striteri("67890\n",  NULL);
   }
   */

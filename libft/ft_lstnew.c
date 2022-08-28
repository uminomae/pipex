/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hioikawa </var/mail/hioikawa>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:22:45 by hioikawa          #+#    #+#             */
/*   Updated: 2022/02/21 05:31:47 by hioikawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*p_node;

	p_node = (t_list *)malloc(sizeof(t_list) * 1);
	if (p_node == NULL)
		return (NULL);
	p_node -> content = content;
	p_node -> next = NULL;
	return (p_node);
}

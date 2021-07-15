/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrhyhorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 20:19:22 by jrhyhorn          #+#    #+#             */
/*   Updated: 2020/11/24 20:19:36 by jrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*node;
	int		count;

	count = 1;
	node = lst;
	if (node == NULL)
		return (0);
	else
	{
		while (node->next)
		{
			count += 1;
			node = node->next;
		}
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrhyhorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 20:19:59 by jrhyhorn          #+#    #+#             */
/*   Updated: 2020/11/24 20:22:21 by jrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*ps;

	i = 0;
	ps = (unsigned char *)s;
	while (n--)
	{
		if (ps[i] == (unsigned char)c)
			return (&ps[i]);
		i++;
	}
	return (NULL);
}

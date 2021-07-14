/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchin <dchin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:18:53 by dchin             #+#    #+#             */
/*   Updated: 2020/11/11 16:03:48 by dchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	int				i;
	unsigned char	*src;

	src = (unsigned char*)str;
	i = 0;
	while (n > 0)
	{
		if (src[i] == (unsigned char)c)
			return ((void*)(src + i));
		n--;
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrhyhorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:12:30 by jrhyhorn          #+#    #+#             */
/*   Updated: 2020/11/24 20:13:04 by jrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*pdest;
	const unsigned char	*psrc;

	i = 0;
	pdest = (unsigned char *)dest;
	psrc = (const unsigned char *)src;
	if (!pdest && !psrc)
		return (NULL);
	while (i < n)
	{
		pdest[i] = psrc[i];
		if (psrc[i] == (unsigned char)c)
			return (pdest + i + 1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrhyhorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 20:10:21 by jrhyhorn          #+#    #+#             */
/*   Updated: 2020/11/24 20:11:03 by jrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*psrc;
	char	*pdest;

	psrc = (char *)src;
	pdest = (char *)dest;
	if ((dest == src) || !n)
		return (dest);
	if (psrc < pdest)
	{
		while (n--)
			pdest[n] = psrc[n];
	}
	else if (psrc >= pdest)
	{
		while (n--)
			*pdest++ = *psrc++;
	}
	return (dest);
}

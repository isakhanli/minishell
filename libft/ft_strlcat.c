/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrhyhorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 20:07:14 by jrhyhorn          #+#    #+#             */
/*   Updated: 2020/11/28 11:17:29 by jrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	size_t	d;
	size_t	s;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	d = dst_len;
	s = 0;
	if (size == 0)
		return (src_len);
	if (dst_len > size - 1)
		return (src_len + size);
	while (src[s] != '\0' && d < (size - 1))
		dst[d++] = src[s++];
	dst[d] = '\0';
	return (dst_len + src_len);
}

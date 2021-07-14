/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchin <dchin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:25:22 by dchin             #+#    #+#             */
/*   Updated: 2020/11/11 16:05:16 by dchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t count)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(src);
	while (dest[i] && i < count)
		i++;
	while (src[j] && (i + j + 1) < count)
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < count)
		dest[i + j] = '\0';
	return (i + len);
}

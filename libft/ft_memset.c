/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrhyhorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 20:16:59 by jrhyhorn          #+#    #+#             */
/*   Updated: 2020/11/24 20:17:25 by jrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*pstr;

	i = 0;
	pstr = s;
	while (i < n)
	{
		*pstr = (unsigned char)c;
		pstr++;
		i++;
	}
	return (s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchin <dchin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:37:12 by dchin             #+#    #+#             */
/*   Updated: 2020/11/11 17:06:39 by dchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (c == 0)
	{
		while (str[i])
			i++;
		return ((char*)(str + i));
	}
	while (str[i])
	{
		if (str[i] == c)
			return ((char*)(str + i));
		i++;
	}
	return (NULL);
}

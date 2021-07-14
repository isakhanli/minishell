/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchin <dchin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 23:20:45 by dchin             #+#    #+#             */
/*   Updated: 2020/11/13 19:37:46 by dchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_little;
	size_t	len_big;

	if (!little[0])
		return ((char*)(big));
	len_little = ft_strlen(little);
	len_big = ft_strlen(big);
	if (len_big < len_little || len < len_little)
		return (NULL);
	i = 0;
	while (big[i] && i <= len - len_little)
	{
		j = 0;
		while (little[j] && big[i + j] == little[j])
			j++;
		if (!little[j])
			return ((char*)(big + i));
		i++;
	}
	return (NULL);
}

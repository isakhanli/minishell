/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchin <dchin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 00:29:43 by dchin             #+#    #+#             */
/*   Updated: 2020/11/11 16:05:21 by dchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*ptr;

	len = 0;
	i = 0;
	while (s[len] != '\0')
		len++;
	if (!(ptr = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (len > 0)
	{
		ptr[i] = s[i];
		i++;
		len--;
	}
	ptr[i] = '\0';
	return (ptr);
}

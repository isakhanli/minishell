/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrhyhorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 20:03:38 by jrhyhorn          #+#    #+#             */
/*   Updated: 2020/11/24 20:08:37 by jrhyhorn         ###   ########.fr       */
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
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
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

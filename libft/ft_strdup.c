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
/*
char	*ft_strdup(const char *s)
{
	int		len;
	char	*s2;

	len = ft_strlen(s);
	s2 = malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	if (ft_memcpy(s2, s, len))
	{
		s2[len] = '\0';
		return (s2);
	}
	return (0);
}
*/
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrhyhorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:56:03 by jrhyhorn          #+#    #+#             */
/*   Updated: 2020/11/24 19:51:36 by jrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s3;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1);
	while (i < j && s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j > i && s1[j - 1] && ft_strchr(set, s1[j - 1]))
		j--;
	s3 = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!s3)
		return (NULL);
	while (i < j && s1[i])
		s3[k++] = s1[i++];
	s3[k] = '\0';
	return (s3);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchin <dchin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:45:39 by dchin             #+#    #+#             */
/*   Updated: 2020/11/11 16:05:06 by dchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		check_in_set(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int		check_beginning(char const *s1, char const *set)
{
	int i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (!(check_in_set(s1[i], set)))
			return (i);
		i++;
	}
	return (i);
}

static int		check_ending(char const *s1, char const *set)
{
	int len;

	len = ft_strlen(s1) - 1;
	while (len > 0)
	{
		if (!(check_in_set(s1[len], set)))
			return (len);
		len--;
	}
	return (len);
}

static int		check_blank_input(char const *s1, char const *set)
{
	int len;
	int check;

	len = ft_strlen(s1);
	check = check_beginning(s1, set);
	if (len == check)
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		beggining;
	int		ending;
	int		len;
	int		i;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	beggining = check_beginning(s1, set);
	ending = check_ending(s1, set) + 1;
	len = (ending - beggining);
	if ((check_blank_input(s1, set)))
	{
		if (!(ptr = (char*)malloc((sizeof(char)))))
			return (NULL);
		ptr[0] = '\0';
		return (ptr);
	}
	if (!(ptr = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (i < len)
		ptr[i++] = s1[beggining++];
	ptr[i] = '\0';
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrhyhorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:59:51 by jrhyhorn          #+#    #+#             */
/*   Updated: 2020/11/27 01:13:27 by jrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *str, char c)
{
	int		count;
	int		flag;

	flag = 0;
	count = 0;
	while (*str != '\0')
	{
		if (*str == (unsigned char)c)
			flag = 0;
		else if (flag != 1)
		{
			count += 1;
			flag = 1;
		}
		else if (flag == 0)
			flag = 1;
		str++;
	}
	return (count);
}

static int	ft_word_lenth(const char *s, char c)
{
	int		count;

	count = 0;
	while (*(s + count) != '\0' && *(s + count) != c)
		count++;
	return (count);
}

static char	**ft_free_arr(char **s)
{
	while (*s)
		free(*s++);
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		w;
	int		i;
	int		w_lenth;

	if (!s)
		return (NULL);
	i = -1;
	w = ft_word_count(s, c);
	arr = (char **)malloc(sizeof(char *) * (w + 1));
	if (!arr)
		return (NULL);
	while (i < w)
	{
		while (*s != '\0' && *s == c)
			s++;
		w_lenth = ft_word_lenth(s, c);
		arr[i] = (char *)malloc(sizeof(char) * (w_lenth + 1));
		if (!arr)
			return (ft_free_arr(arr));
		arr[w] = ft_memcpy(arr[i], s, w_lenth);
		arr[w][w_lenth] = '\0';
		s += w_lenth;
		i++;
	}
	arr[w] = (void *)0;
	return (arr);
}

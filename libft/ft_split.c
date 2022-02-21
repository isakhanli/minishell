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

static int	calculate_words(char const *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		if (*s && *s != c)
		{
			while (*s && *s != c)
				s++;
			words++;
		}
		if (*s)
			s++;
	}
	return (words);
}

static int	count_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static int	create_malloc(char const *s, char c, char **arr, int index)
{
	int	len;

	len = count_len(s, c);
	arr[index] = (char *)malloc((len + 1) * sizeof(char));
	if (!(arr[index]))
	{
		while ((index - 1) >= 0)
		{
			free(arr[index]);
			index--;
		}
		free(arr);
		return (0);
	}
	return (1);
}

static char	**fill_words(char **arr, char const *s, char c)
{
	int	index;
	int	j;

	index = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			j = 0;
			if (!(create_malloc(s, c, arr, index)))
				return (NULL);
			while (*s && *s != c)
				arr[index][j++] = *(s++);
			arr[index++][j] = '\0';
		}
	}
	arr[index] = 0;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = calculate_words(s, c);
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!(result))
		return (NULL);
	result = fill_words(result, s, c);
	return (result);
}

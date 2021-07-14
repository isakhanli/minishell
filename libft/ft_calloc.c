/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchin <dchin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 23:57:39 by dchin             #+#    #+#             */
/*   Updated: 2020/11/11 16:01:37 by dchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	int		total_size;

	total_size = nmemb * size;
	if (!(p = malloc(total_size)))
		return (NULL);
	ft_bzero(p, total_size);
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrhyhorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:13:01 by jrhyhorn          #+#    #+#             */
/*   Updated: 2020/11/24 20:06:14 by jrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long	r;
	int				sign;

	r = 0;
	sign = 1;
	while ((*str == '\t' || *str == '\n' || *str == ' ' || *str == '\r'
			|| *str == '\v' || *str == '\f') && *str != '\0')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str - '0' < 0 || *str - '0' > 9)
			return (r * sign);
		r = r * 10 + (*str - '0');
		str++;
	}
	return ((int)(r * sign));
}

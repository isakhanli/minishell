/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchin <dchin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:46:12 by dchin             #+#    #+#             */
/*   Updated: 2020/11/11 16:02:01 by dchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_len_n(long nb)
{
	int		i;
	int		minus;
	long	n;

	n = nb;
	minus = (n < 0 ? 1 : 0);
	if (n < 0)
		n = -n;
	i = 1;
	while (n / 10 >= 1)
	{
		n /= 10;
		i++;
	}
	if (minus)
		return (i + minus);
	return (i);
}

char			*ft_itoa(int n)
{
	long	nb;
	int		len_n;
	char	*a;

	nb = (long)n;
	len_n = ft_len_n(nb);
	if (!(a = (char*)malloc((len_n + 1) * sizeof(char))))
		return (NULL);
	if (nb < 0)
		a[0] = '-';
	nb = (nb < 0 ? -nb : nb);
	a[len_n] = '\0';
	if (nb == 0 || nb == -0)
	{
		a[0] = '0';
		return (a);
	}
	while (nb >= 1)
	{
		a[len_n - 1] = nb % 10 + 48;
		nb /= 10;
		len_n--;
	}
	return (a);
}

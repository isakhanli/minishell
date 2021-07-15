/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrhyhorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:26:59 by jrhyhorn          #+#    #+#             */
/*   Updated: 2020/11/24 19:46:53 by jrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_rev(char *s)
{
	int		i;
	int		j;
	char	buf;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		buf = s[i];
		s[i] = s[j];
		s[j] = buf;
		i++;
		j--;
	}
	return (s);
}

static int	len(long int nn)
{
	int	count;

	if (nn == 0)
		return (1);
	count = 1;
	if (nn < 0)
	{
		nn = -nn;
		count += 1;
	}
	while ((nn /= 10) > 0)
		count++;
	return (count);
}

static void	*zerostr(char *s)
{
	s[0] = '0';
	s[1] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	long int	i;
	int			sign;
	char		*str;
	long int	nn;

	i = 0;
	nn = (long int)n;
	if (!(str = (char *)malloc(sizeof(char) * (len(nn) + 1))))
		return (NULL);
	if (nn == 0)
		return (zerostr(str));
	if ((sign = nn) < 0)
		nn = -nn;
	while (nn > 0)
	{
		str[i++] = nn % 10 + '0';
		nn = nn / 10;
	}
	if (sign < 0)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_rev(str));
}

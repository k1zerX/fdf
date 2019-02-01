/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:50:37 by kbatz             #+#    #+#             */
/*   Updated: 2018/11/30 19:39:22 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		itoa_len(int n)
{
	int		len;

	len = 1;
	n /= 10;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	int		i;
	int		len;
	char	*res;
	char	sign;

	sign = 1;
	len = itoa_len(n);
	if (n < 0)
		sign = -1 + 0 * len++;
	res = ft_strnew(len);
	if (res)
	{
		if (sign == -1)
			res[0] = '-';
		i = len;
		while (--i >= -1 * (sign - 1) / 2)
		{
			res[i] = n % 10 * sign + 48;
			n /= 10;
		}
	}
	return (res);
}

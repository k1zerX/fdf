/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 20:05:39 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/01 01:20:38 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	long	res;
	long	buf;
	char	sign;

	buf = 0;
	res = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = -1 * (str[i++] - 44);
	while (ft_isdigit(str[i]))
	{
		buf = res;
		res = res * 10 + sign * (str[i++] - '0');
		if (buf > 0 && buf > res)
			return (-1);
		if (buf < 0 && buf < res)
			return (0);
	}
	return ((int)res);
}
